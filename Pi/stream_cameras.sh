#!/bin/bash

output_url="udp://192.168.2.1"
base_port=50000

WIDTH=640
HEIGHT=480
FPS=30
PIX_FORMAT="mjpeg"     # 

in_args="-hide_banner -loglevel warning -f v4l2 -input_format ${PIX_FORMAT} -video_size ${WIDTH}x${HEIGHT} -framerate ${FPS}"
out_args="-c:v copy -f mjpeg -flush_packets 1"

devnums=(0 2 4 6)

RESTART_COOLDOWN=3     

echo "[init] Clearing any stale ffmpeg holders on the camera nodes..."
killall -q ffmpeg 2>/dev/null
sleep 1

if command -v v4l2-ctl >/dev/null 2>&1; then
    echo "[init] Detected video devices:"
    v4l2-ctl --list-devices 2>/dev/null
else
    echo "[init] v4l2-ctl not installed; skipping capability dump (apt install v4l-utils)."
fi

stream_camera() {
    local dev=$1
    local port=$2

    while true; do
        device="/dev/video$dev"

        if [[ ! -e "$device" ]]; then
            echo "[$device] missing, waiting..."
            sleep "$RESTART_COOLDOWN"
            continue
        fi

        echo "Starting stream for $device -> $output_url:$port (${WIDTH}x${HEIGHT}@${FPS} ${PIX_FORMAT})"

        ffmpeg \
            $in_args \
            -i "$device" \
            $out_args \
            "$output_url:$port"

        status=$?

        echo "[$device] ffmpeg exited with status $status; restarting in ${RESTART_COOLDOWN}s"

        sleep "$RESTART_COOLDOWN"
    done
}

pids=()

cleanup() {
    echo "[exit] Stopping all camera streams..."
    kill "${pids[@]}" 2>/dev/null
    killall -q ffmpeg 2>/dev/null
}
trap cleanup EXIT INT TERM

for i in "${!devnums[@]}"; do
    dev=${devnums[$i]}
    port=$((base_port + i))

    stream_camera "$dev" "$port" &
    pids+=($!)
done

wait
