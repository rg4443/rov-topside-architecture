# ROV Topside Architecture

Topside control and computer vision stack for a MATE ROV competition vehicle (2026 global championship). This repo covers the surface-side software: multi-camera video ingestion, real-time object detection, pilot input, and an on-demand 3D reconstruction (photogrammetry) pipeline built from ROV-captured imagery.

The system is split across two physical machines connected by a tether:

- **`Pi/`** runs on the ROV itself (Raspberry Pi). Discovers and streams onboard cameras over UDP to the surface.
- **`Topside/`** runs on the surface control laptop. Receives the video streams, runs real-time inference, handles pilot controller input, and can trigger a full 3D reconstruction of captured images.

## Why this exists

MATE ROV missions score on a robot's ability to complete tasks underwater and report on what it sees. This year's mission includes identifying and counting an invasive species (European green crab). The topside stack needed to:

1. Ingest multiple live camera feeds from the ROV with low, bounded latency and automatic recovery from dropped/frozen streams.
2. Run object detection on the primary feed in real time, without stalling the video pipeline.
3. Let the pilot capture still images on demand (controller button) for later 3D reconstruction of the seafloor/mission props.
4. Turn a folder of captured images into a textured 3D mesh, without requiring a CUDA GPU on the topside machine.

## Architecture

```
   ROV (Raspberry Pi)                         Topside (surface laptop)
┌───────────────────────┐                 ┌────────────────────────────────────┐
│ stream_cameras.sh     │    UDP/ffmpeg   | camera_worker (x3, isolated procs) │
│ - auto-discovers      │  -------------> |  - writes frames into shared       │
│   /dev/v4l cameras    │   MJPG/H264/    |    memory (zero-copy numpy views)  │
│ - format/resolution   │   YUYV, per-cam │                                    |
│   negotiation         │                 │ inference_worker (isolated proc)   │
│ - stall watchdog +    │                 │  - YOLOv11 (best.pt) on cam 0      │
│   auto-restart per cam│                 │  - live bounding boxes + crab      │
└───────────────────────┘                 │    count overlay                   │
                                          │                                    │
                                          │ pygame joystick loop               │
                                          │  - snapshot capture (A)            │
                                          │  - delete last capture (X)         │
                                          │  - trigger photogrammetry (B)      │
                                          │                                    │
                                          │ combine() -> 1920x1080 HUD         │
                                          │  main feed (AI or raw) on top,     │
                                          │  two helper feeds tiled below      │
                                          └────────────────────────────────────┘
                                                          |
                                                          ▼
                                           ┌──────────────────────────────────┐
                                           │ Photogrammetry pipeline (Docker) │
                                           │  COLMAP (sparse, CPU-only)       │
                                           │   - OpenMVS (dense/mesh/texture) │
                                           │   - final_model.obj + textures   │
                                           └──────────────────────────────────┘
```

## Computer vision & systems highlights

- **Multi-process, shared-memory video pipeline.** Each camera feed and the inference stage run as isolated OS processes (`multiprocessing`), communicating through `shared_memory` buffers rather than pickled frames over pipes. This avoids per-frame serialization overhead and keeps a slow inference pass from blocking camera capture.
- **Real-time detection without stalling the feed.** `inference_worker` polls a frame-tick counter and only runs YOLO when a new frame has actually landed, decoupling inference framerate from the display/capture loop. The UI shows "AI: LOADING…" while the model warms up and falls back to the raw feed if inference is off, so the pilot is never staring at a frozen frame.
- **Adaptive camera streaming on the ROV side.** `stream_cameras.sh` probes each `/dev/v4l` device for supported pixel formats and resolutions, prefers hardware-friendly formats in priority order (H264 -> MJPG -> YUYV), and picks the closest supported resolution to the target. A per-camera watchdog detects a stalled `ffmpeg` process (no progress on its progress file) and restarts it independently, so one bad USB camera doesn't take down the whole stream.
- **Structure-from-motion / 3D reconstruction.** A separate, Dockerized pipeline runs COLMAP for sparse reconstruction (feature extraction + camera pose estimation, forced CPU-only with `--dense 0`) and hands off to OpenMVS for dense point cloud generation, meshing, and texture baking, producing a textured `.obj` from a folder of ROV-captured stills, without needing an NVIDIA GPU on the topside laptop.
- **Fault isolation by design.** Camera capture, inference, and the (optional) telemetry logger all run in separate processes behind an `interrupt_event`, so a crash in one doesn't take the others down, and shutdown cleanly unwinds shared memory handles.

## Repo structure

| Path                                     | Purpose                                                                                                                                                                                                                 |
| ---------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Pi/stream_cameras.sh`                   | Onboard (ROV): discovers `/dev/v4l` cameras, negotiates pixel format/resolution, streams each feed to topside over UDP via `ffmpeg`, with a per-camera stall watchdog and auto-restart                                  |
| `Topside/cameras.py`                     | Surface: receives the UDP streams, runs multi-process shared-memory capture, real-time YOLOv11 inference on the main feed, pilot controller input (capture/delete/trigger-photogrammetry), and renders the combined HUD |
| `Topside/test_cameras.py`                | Local dev/test variant of `cameras.py`, reads from local webcams instead of UDP streams, no pygame/controller dependency                                                                                                |
| `Topside/best.pt (git ignored)`          | YOLOv11 weights, trained for green-crab detection/counting                                                                                                                                                              |
| `Topside/Dockerfile`                     | Build for the photogrammetry pipeline image (COLMAP + OpenMVS)                                                                                                                                                          |
| `Topside/run_photogrammetry_pipeline.sh` | Launches the photogrammetry Docker container with the correct X11/display flags for the host OS                                                                                                                         |
| `Topside/requirements.txt`               | Python dependencies for the topside app                                                                                                                                                                                 |

## Getting started

**Topside (surface laptop):**

```bash
cd Topside
pip install -r requirements.txt
python3 cameras.py
```

Controls: `i` toggles AI inference on the main feed, controller `A` captures an image, `X` deletes the most recent capture, `B` triggers the photogrammetry pipeline in a background thread. `q` quits.

**ROV (Raspberry Pi):**

```bash
cd Pi
chmod +x stream_cameras.sh
./stream_cameras.sh
```

**Photogrammetry pipeline (Docker, no local CUDA required):**

```bash
cd Topside
docker build --platform linux/amd64 -t stream-capture-pipeline .
./run_photogrammetry_pipeline.sh
```

## Full documentation

Detailed design docs, decisions, and mission-context writeup are in `docs/mate-rov-software-documentation.pdf`. Details performance and data collection from this pipeline.

## Status / known gaps

- `test_cameras.py` currently duplicates most of `cameras.py`'s logic against local webcams instead of UDP streams, is a candidate for consolidating into a `--source` flag.
