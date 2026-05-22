#!/bin/bash

output_url="udp://192.168.2.1"
base_port=50000

in_args="-hide_banner -loglevel error -f v4l2 -input_format mjpeg -re"
out_args="-c:v copy -preset ultrafast -tune zerolatency -f mjpeg -flush_packets 1"

devnums=(0 2 4 6)

stream_camera() {
    local dev=$1
    local port=$2

    while true; do
        device="/dev/video$dev"

        if [[ ! -e "$device" ]]; then
            echo "[$device] missing, waiting..."
            sleep 1
            continue
        fi

        echo "Starting stream for $device -> $output_url:$port"

        ffmpeg \
            $in_args \
            -i "$device" \
            $out_args \
            "$output_url:$port"

        status=$?

        echo "[$device] ffmpeg exited with status $status"

        sleep 1
    done
}

pids=()

for i in "${!devnums[@]}"; do
    dev=${devnums[$i]}
    port=$((base_port + i))

    stream_camera "$dev" "$port" &
    pids+=($!)
done

wait
