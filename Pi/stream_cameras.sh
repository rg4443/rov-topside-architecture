
output_url="udp://192.168.2.1"
base_port=50000
RESTART_COOLDOWN=3
STARTUP_STAGGER=2          # seconds between launches; spreads USB inrush at startup

TARGET_W=640
TARGET_H=480
TARGET_FPS=30

STARTUP_STAGGER=2
FORMAT_PRIORITY=(H264 MJPG YUYV)

devnums=(0 2 4 6)
BYPATH=/dev/v4l/by-path

# Fallback only (used if /dev/v4l/by-path is unavailable): raw node numbers.
devnums=(0 4 6 8)

# --------------------------------------------------------------------------- #

have_v4l2ctl() { command -v v4l2-ctl >/dev/null 2>&1; }

is_capture_device() {
    local dev=$1
    have_v4l2ctl || return 0   
    have_v4l2ctl || return 0
    v4l2-ctl -d "$dev" --list-formats-ext 2>/dev/null | grep -q "'.*'"
}

# Highest-priority fourcc a node advertises (per FORMAT_PRIORITY).
detect_fourcc() {
    local dev=$1 fmts
    local dev=$1 fmts fmt
    fmts=$(v4l2-ctl -d "$dev" --list-formats-ext 2>/dev/null)
    if   grep -q "'MJPG'" <<<"$fmts"; then echo "MJPG"
    elif grep -q "'H264'" <<<"$fmts"; then echo "H264"
    elif grep -q "'YUYV'" <<<"$fmts"; then echo "YUYV"
    else echo ""
    fi
    for fmt in "${FORMAT_PRIORITY[@]}"; do
        grep -q "'$fmt'" <<<"$fmts" && { echo "$fmt"; return; }
    done
    echo ""
}

sizes_for() {
        }'
}

# Target resolution if the camera offers it, else the smallest advertised size.
pick_resolution() {
    local dev=$1 fourcc=$2 list
    [ -z "$fourcc" ] && { echo ""; return; }
    echo "$list" | awk -Fx '{print $1*$2, $1"x"$2}' | sort -n | head -1 | awk '{print $2}'
}

# Build ffmpeg IN_ARGS/OUT_ARGS for a concrete /dev/videoX node.
build_args() {
    local dev=$1 fourcc res ifmt
    local node=$1 fourcc res ifmt
    IN_ARGS="-hide_banner -loglevel warning -f v4l2"

    if ! have_v4l2ctl; then
        return
    fi

    fourcc=$(detect_fourcc "$dev")
    res=$(pick_resolution "$dev" "$fourcc")
    fourcc=$(detect_fourcc "$node")
    res=$(pick_resolution "$node" "$fourcc")

    case "$fourcc" in
        MJPG) ifmt="mjpeg";   OUT_ARGS="-c:v copy -f mjpeg -flush_packets 1" ;;          
        H264) ifmt="h264";    OUT_ARGS="-c:v copy -f mpegts -flush_packets 1" ;;        
        YUYV) ifmt="yuyv422"; OUT_ARGS="-c:v mjpeg -q:v 5 -f mjpeg -flush_packets 1" ;;  