#!/bin/bash
set -e

echo "Running Photogrammetry Docker Pipeline on Native Linux"

xhost +local:root

docker run --rm -it \
  --net=host \
  --ipc=host \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v "$(pwd):/workspace" \
  --device /dev/input \
  stream-capture-pipeline

xhost -local:root

echo "Pipeline completed"