#!/bin/bash

output_url="udp://192.168.2.1"
base_port=50000
RESTART_COOLDOWN=3

TARGET_W=640
TARGET_H=480
TARGET_FPS=30

devnums=(0 2 4 6)


have_v4l2ctl() { command -v v4l2-ctl >/dev/null 2>&1; }

is_capture_device() {
    local dev=$1
    have_v4l2ctl || return 0   
    v4l2-ctl -d "$dev" --list-formats-ext 2>/dev/null | grep -q "'.*'"
}

detect_fourcc() {
    local dev=$1 fmts
    fmts=$(v4l2-ctl -d "$dev" --list-formats-ext 2>/dev/null)
    if   grep -q "'MJPG'" <<<"$fmts"; then echo "MJPG"
    elif grep -q "'YUYV'" <<<"$fmts"; then echo "YUYV"
    else echo ""
    fi
}

sizes_for() {
    local dev=$1 fourcc=$2
    v4l2-ctl -d "$dev" --list-formats-ext 2>/dev/null | awk -v f="$fourcc" '
        /\[[0-9]+\]:/ { inblk = (index($0, "\x27" f "\x27") > 0) }
        inblk && /Size: Discrete/ {
            for (i = 1; i <= NF; i++)
                if ($i ~ /^[0-9]+x[0-9]+$/) print $i
        }'
}

pick_resolution() {
    local dev=$1 fourcc=$2 list
    [ -z "$fourcc" ] && { echo ""; return; }
    list=$(sizes_for "$dev" "$fourcc")
    [ -z "$list" ] && { echo ""; return; }
    if grep -qx "${TARGET_W}x${TARGET_H}" <<<"$list"; then
        echo "${TARGET_W}x${TARGET_H}"; return
    fi
    echo "$list" | awk -Fx '{print $1*$2, $1"x"$2}' | sort -n | head -1 | awk '{print $2}'
}

build_args() {
    local dev=$1 fourcc res ifmt
    IN_ARGS="-hide_banner -loglevel warning -f v4l2"
    OUT_ARGS="-f mjpeg -flush_packets 1"

    if ! have_v4l2ctl; then
        IN_ARGS="$IN_ARGS -input_format mjpeg"
        OUT_ARGS="-c:v copy $OUT_ARGS"
        CONFIG_DESC="mjpeg/copy (unprobed: v4l2-ctl missing)"
        return
    fi

    fourcc=$(detect_fourcc "$dev")
    res=$(pick_resolution "$dev" "$fourcc")

    case "$fourcc" in
        MJPG) ifmt="mjpeg";    OUT_ARGS="-c:v copy $OUT_ARGS" ;;   
        YUYV) ifmt="yuyv422";  OUT_ARGS="-c:v mjpeg -q:v 5 $OUT_ARGS" ;;  
        *)    ifmt="";         OUT_ARGS="-c:v mjpeg -q:v 5 $OUT_ARGS" ;;
    esac

    [ -n "$ifmt" ] && IN_ARGS="$IN_ARGS -input_format $ifmt"
    [ -n "$res" ]  && IN_ARGS="$IN_ARGS -video_size $res"
    IN_ARGS="$IN_ARGS -framerate $TARGET_FPS"
    CONFIG_DESC="${ifmt:-default}/${OUT_ARGS%% -f *} @ ${res:-camera-default} ${TARGET_FPS}fps"
}

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

        build_args "$dev"
        echo "Starting stream for $device -> $output_url:$port  [$CONFIG_DESC]"

        ffmpeg $IN_ARGS -i "$device" $OUT_ARGS "$output_url:$port"
        status=$?

        echo "[$device] ffmpeg exited with status $status; restarting in ${RESTART_COOLDOWN}s"
        sleep "$RESTART_COOLDOWN"
    done
}

echo "[init] Clearing any stale ffmpeg holders on the camera nodes..."
killall -q ffmpeg 2>/dev/null
sleep 1

if ! have_v4l2ctl; then
    echo "[init] WARNING: v4l2-ctl not installed (apt install v4l-utils)."
    echo "[init] Falling back to unprobed MJPEG-copy; install v4l-utils for adaptive mode."
fi

active=()
for dev in "${devnums[@]}"; do
    device="/dev/video$dev"
    if [[ ! -e "$device" ]]; then
        echo "[init] $device not present, skipping."
        continue
    fi
    if ! is_capture_device "$device"; then
        echo "[init] $device is not a video-capture node (metadata/output), skipping."
        continue
    fi
    if have_v4l2ctl; then
        echo "[init] $device capabilities:"
        v4l2-ctl -d "$device" --list-formats-ext 2>/dev/null | sed 's/^/        /'
    fi
    active+=("$dev")
done

if [ ${#active[@]} -eq 0 ]; then
    echo "[init] No usable capture devices found. Check connections / 'v4l2-ctl --list-devices'."
    exit 1
fi
echo "[init] Streaming devices: ${active[*]/#//dev/video}"

pids=()
cleanup() {
    echo "[exit] Stopping all camera streams..."
    kill "${pids[@]}" 2>/dev/null
    killall -q ffmpeg 2>/dev/null
}
trap cleanup EXIT INT TERM

for i in "${!active[@]}"; do
    dev=${active[$i]}
    port=$((base_port + i))
    stream_camera "$dev" "$port" &
    pids+=($!)
done

wait
