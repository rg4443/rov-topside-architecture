import cv2
from ultralytics import YOLO
import multiprocessing as mp
from multiprocessing import shared_memory
import numpy as np
import os
import shutil
import subprocess
import time
import csv
import threading
import sys

IMAGE_FOLDER = os.path.abspath("images")
OUTPUT_FOLDER = os.path.abspath("output")
CACHE_FOLDER = os.path.abspath("cache")

ENABLE_LOGGING = False
FRAME_SHAPE = (1080, 1920, 3)
FRAME_SIZE_BYTES = np.prod(FRAME_SHAPE) * np.dtype(np.uint8).itemsize

def init_folders():
    os.makedirs(CACHE_FOLDER, exist_ok=True)
    
    if os.path.exists(OUTPUT_FOLDER):
        try:
            shutil.rmtree(OUTPUT_FOLDER)
        except Exception as e:
            print(f"Failed to remove {OUTPUT_FOLDER}: {e}")
    os.makedirs(OUTPUT_FOLDER, exist_ok=True)
    
    os.makedirs(IMAGE_FOLDER, exist_ok=True)


def camera_worker(camera_id, url, shm_name, sync_dict, interrupt_event):
    """
    Isolated process capturing video frames and pushing them directly
    into Shared Memory via a non-allocating memory copy.
    """
    print(f"[Executive] Initializing Stream {camera_id}...")
    
    existing_shm = shared_memory.SharedMemory(name=shm_name)
    shared_array = np.ndarray(FRAME_SHAPE, dtype=np.uint8, buffer=existing_shm.buf)
    
    video = cv2.VideoCapture(url)
    video.set(cv2.CAP_PROP_BUFFERSIZE, 1)
    
    last_heartbeat = time.time()
    timeout_threshold = 2.0
    first_frame_received = False
    recovery_start = time.time()

    try:
        while not interrupt_event.is_set():
            start_time = time.time()
            r, f = video.read()
            
            if r and f is not None:
                if not first_frame_received and ENABLE_LOGGING:
                    duration = time.time() - recovery_start
                    with open("recovery_performance.csv", mode='a', newline='') as rf:
                        csv.writer(rf).writerow([time.strftime("%H:%M:%S"), camera_id, f"{duration:.3f}"])
                    first_frame_received = True

                np.copyto(shared_array, f)
                
                sync_dict[f"lat_{camera_id}"] = start_time
                sync_dict[f"frame_tick_{camera_id}"] = sync_dict.get(f"frame_tick_{camera_id}", 0) + 1
                
                last_heartbeat = time.time()
            
            if (time.time() - last_heartbeat) > timeout_threshold:
                print(f"[Watchdog] Stream {camera_id} HEARTBEAT LOST.")
                time.sleep(1.0)
                last_heartbeat = time.time()
                
    finally:
        video.release()
        existing_shm.close()


def inference_worker(raw_shm_name, out_shm_name, sync_dict, interrupt_event):
    """
    Isolated process processing Camera 0 frames using YOLO. Runs sequentially
    to completely avoid Python GIL locking conditions.
    """
    model = YOLO("best.pt")
    
    raw_shm = shared_memory.SharedMemory(name=raw_shm_name)
    raw_array = np.ndarray(FRAME_SHAPE, dtype=np.uint8, buffer=raw_shm.buf)
    
    out_shm = shared_memory.SharedMemory(name=out_shm_name)
    out_array = np.ndarray(FRAME_SHAPE, dtype=np.uint8, buffer=out_shm.buf)
    
    last_tick = -1
    
    try:
        while not interrupt_event.is_set():
            current_tick = sync_dict.get("frame_tick_0", 0)
            
            if current_tick != last_tick:
                last_tick = current_tick
                
                inf_start = time.time()
                results = model.predict(raw_array, verbose=False)
                inf_duration = time.time() - inf_start
                
                annotated = results[0].plot()
                number = len(results[0].boxes)
                cv2.putText(annotated, f"Green Crabs: {number}", (7, 70),
                            cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)
                
                np.copyto(out_array, annotated)
                sync_dict["inference_time"] = inf_duration
            else:
                time.sleep(0.002)
                
    finally:
        raw_shm.close()
        out_shm.close()


def telemetry_logger(sync_dict, interrupt_event, filename="vision_performance.csv"):
    if not ENABLE_LOGGING: return
    
    with open(filename, mode='w', newline='') as f:
        csv.writer(f).writerow(["Timestamp", "Total_AI_Stream_Lat", "Pure_AI_Inference", "Raw_1", "Raw_2", "Raw_3", "FPS"])

    while not interrupt_event.is_set():
        time.sleep(10)
        timestamp = time.strftime("%H:%M:%S")
        now = time.time()
        
        pure_inf = sync_dict.get("inference_time", 0.0)
        fps = 1.0 / pure_inf if pure_inf > 0 else 0.0
        
        total_lat_0 = now - sync_dict.get("lat_0", now)
        total_lat_1 = now - sync_dict.get("lat_1", now)
        total_lat_2 = now - sync_dict.get("lat_2", now)
        total_lat_3 = now - sync_dict.get("lat_3", now)
        
        row = [timestamp, total_lat_0, pure_inf, total_lat_1, total_lat_2, total_lat_3, f"{fps:.2f}"]
        
        with open(filename, mode='a', newline='') as f:
            csv.writer(f).writerow(row)

clean_openmvs_env = os.environ.copy()
if "LD_LIBRARY_PATH" in clean_openmvs_env:
    paths = clean_openmvs_env["LD_LIBRARY_PATH"].split(":")
    clean_paths = [p for p in paths if "openmvs_libs" not in p]
    clean_openmvs_env["LD_LIBRARY_PATH"] = ":".join(clean_paths)

openmvs_env = os.environ.copy()
openmvs_env["LD_LIBRARY_PATH"] = f"/usr/local/lib/openmvs_libs:{openmvs_env.get('LD_LIBRARY_PATH', '')}"


def run_photogrammetry(status_dict):
    status_dict["generating"] = True
    workspace_dir = os.path.join(OUTPUT_FOLDER, "colmap_workspace")
    mvs_dir = os.path.join(OUTPUT_FOLDER, "mvs_workspace")
    abs_images = os.path.abspath(IMAGE_FOLDER)    
    
    os.makedirs(workspace_dir, exist_ok=True)
    os.makedirs(mvs_dir, exist_ok=True)
    
    total_cores = mp.cpu_count()
    usable_threads = str(max(1, total_cores - 3))

    print(f"[System] Starting Photogrammetry ({usable_threads} threads)...")

    try:
        print("[System] Extracting features and generating sparse map...")
        subprocess.run([
            "colmap", "automatic_reconstructor",
            "--image_path", IMAGE_FOLDER,
            "--workspace_path", workspace_dir,
            "--data_type", "individual",
            "--camera_model", "PINHOLE",
            "--single_camera", "1",
            "--quality", "medium",
            "--use_gpu", "0",
            "--num_threads", usable_threads,
            "--dense", "0"  # Stop before CUDA is required
        ], check=True, env=clean_openmvs_env)

        sparse_zero_dir = os.path.join(workspace_dir, "sparse", "0")
        os.makedirs(sparse_zero_dir, exist_ok=True)
        
        for item in os.listdir(os.path.join(workspace_dir, "sparse")):
            if item.endswith(".bin") and item != "0":
                shutil.move(os.path.join(workspace_dir, "sparse", item), os.path.join(sparse_zero_dir, item))

                print("[System] Converting COLMAP model binaries to TXT format...")
        subprocess.run([
            "colmap", "model_converter",
            "--input_path", sparse_zero_dir,
            "--output_path", os.path.join(workspace_dir, "sparse"),
            "--output_type", "TXT"
        ], check=True, env=clean_openmvs_env)

        nested_img_dir = os.path.join(workspace_dir, "workspace", "images")
        os.makedirs(nested_img_dir, exist_ok=True)
        
        legacy_nested_dir = os.path.join(workspace_dir, "workspace", "output", "colmap_workspace")
        os.makedirs(legacy_nested_dir, exist_ok=True)

        for img_file in os.listdir(IMAGE_FOLDER):
            src_img = os.path.join(IMAGE_FOLDER, img_file)
            if os.path.isfile(src_img):
                shutil.copy(src_img, nested_img_dir)
                shutil.copy(src_img, legacy_nested_dir)

        print("[System] Translating workspace to OpenMVS scene format...")
        subprocess.run([
            "InterfaceCOLMAP",
            "--input-file", workspace_dir,
            "--output-file", "scene.mvs",
            "--image-folder", abs_images,
            "--archive-type", "-1"
        ], check=True, cwd=mvs_dir, env=openmvs_env)

        print("[System] Densifying Point Cloud...")
        subprocess.run([
            "DensifyPointCloud",
            "--input-file", "scene.mvs",
            "--output-file", "scene_dense.mvs",
            "--archive-type", "-1"
        ], check=True, cwd=mvs_dir, env=openmvs_env)

        print("[System] Reconstructing Mesh geometry...")
        subprocess.run([
            "ReconstructMesh",
            "--input-file", "scene_dense.mvs",
            "--output-file", "scene_dense_mesh.mvs",
            "--archive-type", "-1"
        ], check=True, cwd=mvs_dir, env=openmvs_env)

        print("[System] Baking Textures...")
        subprocess.run([
            "TextureMesh",
            "--input-file", "scene_dense_mesh.mvs",
            "--output-file", "scene_dense_mesh_texture.mvs",
            "--export-type", "obj",
            "--archive-type", "-1"
        ], check=True, cwd=mvs_dir, env=openmvs_env)
        
        final_mesh_obj = os.path.join(mvs_dir, "scene_dense_mesh_texture.obj")
        final_mesh_mtl = os.path.join(mvs_dir, "scene_dense_mesh_texture.mtl")
        
        if os.path.exists(final_mesh_obj):
            shutil.copy(final_mesh_obj, os.path.join(OUTPUT_FOLDER, "final_model.obj"))
            shutil.copy(final_mesh_mtl, os.path.join(OUTPUT_FOLDER, "final_model.mtl"))
            
            for file in os.listdir(mvs_dir):
                if file.startswith("scene_dense_mesh_texture_material_0_map_Kd"):
                    ext = file.split('.')[-1]
                    shutil.copy(
                        os.path.join(mvs_dir, file),
                        os.path.join(OUTPUT_FOLDER, f"final_model_material_0_map_Kd.{ext}")
                    )
                    break
            
            obj_path = os.path.join(OUTPUT_FOLDER, "final_model.obj")
            with open(obj_path, 'r') as f:
                obj_content = f.read()
            obj_content = obj_content.replace("scene_dense_mesh_texture.mtl", "final_model.mtl")
            with open(obj_path, 'w') as f:
                f.write(obj_content)

            mtl_path = os.path.join(OUTPUT_FOLDER, "final_model.mtl")
            with open(mtl_path, 'r') as f:
                mtl_content = f.read()
            mtl_content = mtl_content.replace("scene_dense_mesh_texture_material_0_map_Kd", "final_model_material_0_map_Kd")
            with open(mtl_path, 'w') as f:
                f.write(mtl_content)

            print("\n[System] PHOTOGRAMMETRY COMPLETE: final_model.obj is ready in output/ folder!")
        else:
            print("\n[ERROR] Pipeline completed but output mesh file is missing.")
            status_dict["failed"] = True

    except subprocess.CalledProcessError as e:
        status_dict["failed"] = True
        print(f"\n[CRITICAL ERROR] Pipeline failed during binary execution.")
        print(f"Command that crashed: {' '.join(e.cmd)}")
    except FileNotFoundError as e:
        status_dict["failed"] = True
        print(f"\n[ERROR] Missing binary dependency: {e}")
    finally:
        status_dict["generating"] = False

def combine(imgs):
    img1 = cv2.resize(imgs[0], (1920, 1080))
    img2 = cv2.resize(imgs[1], (640, 360))
    img3 = cv2.resize(imgs[2], (640, 360))
    img4 = cv2.resize(imgs[3], (640, 360))
    img5 = cv2.hconcat([img2, img3, img4])
    return cv2.vconcat([img1, img5])

if __name__ == '__main__':
    mp.set_start_method('spawn', force=True)
    init_folders()
    
    if ENABLE_LOGGING:
        with open("recovery_performance.csv", mode='w', newline='') as f:
            csv.writer(f).writerow(["Timestamp", "Camera_ID", "Recovery_Duration_Sec"])

    interrupt_event = mp.Event()
    manager = mp.Manager()
    sync_dict = manager.dict()
    status_dict = manager.dict({"generating": False, "pg_pid": None, "failed": False})
    
    for i in range(4):
        sync_dict[f"lat_{i}"] = time.time()
        sync_dict[f"frame_tick_{i}"] = 0
    sync_dict["inference_time"] = 0.0

    shm_buffers = []
    cam_shm_names = []
    for i in range(4):
        shm = shared_memory.SharedMemory(create=True, size=FRAME_SIZE_BYTES)
        shm_buffers.append(shm)
        cam_shm_names.append(shm.name)
        arr = np.ndarray(FRAME_SHAPE, dtype=np.uint8, buffer=shm.buf)
        arr[:] = 0

    ai_out_shm = shared_memory.SharedMemory(create=True, size=FRAME_SIZE_BYTES)
    shm_buffers.append(ai_out_shm)
    ai_arr = np.ndarray(FRAME_SHAPE, dtype=np.uint8, buffer=ai_out_shm.buf)
    ai_arr[:] = 0

    local_views = [np.ndarray(FRAME_SHAPE, dtype=np.uint8, buffer=shm.buf) for shm in shm_buffers[:4]]
    ai_view = np.ndarray(FRAME_SHAPE, dtype=np.uint8, buffer=ai_out_shm.buf)

    urls = [0, 0, 0, 0]
    processes = []
    for i in range(len(urls)):
        p = mp.Process(target=camera_worker, args=(i, urls[i], cam_shm_names[i], sync_dict, interrupt_event))
        p.daemon = True
        processes.append(p)
        p.start()

    ai_proc = mp.Process(target=inference_worker, args=(cam_shm_names[0], ai_out_shm.name, sync_dict, interrupt_event))
    ai_proc.daemon = True
    processes.append(ai_proc)
    ai_proc.start()

    if ENABLE_LOGGING:
        log_proc = mp.Process(target=telemetry_logger, args=(sync_dict, interrupt_event))
        log_proc.daemon = True
        processes.append(log_proc)
        log_proc.start()

    print("[System] All Vision Processes Active.")
    print("[System] Commencing Automated Headless Test...")

    numPictures = 0
    pg_thread = None

    try:
        while not interrupt_event.is_set():
            imgs = [ai_view] + [local_views[1], local_views[2], local_views[3]]
            
            combined = combine(imgs)
            
            if ENABLE_LOGGING:
                now = time.time()
                lat0 = now - sync_dict.get("lat_0", now)
                cv2.putText(combined, f"Latency: {lat0:.3f}s", (7, 130), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
            
            cv2.imshow('Slugbotics Topside', combined)
            
            key = cv2.waitKey(16) & 0xFF
            
            if key == ord('q'):
                interrupt_event.set()
                
            elif key == ord('p'):
                print(f"[System] Image saved in images/img{numPictures}.jpg")
                filename = os.path.join(IMAGE_FOLDER, f'img{numPictures}.jpg')
                success = cv2.imwrite(filename, local_views[0], [int(cv2.IMWRITE_JPEG_QUALITY), 100])
                if success:
                    print(f"[System] Image successfully saved: {filename}")
                else:
                    print(f"[ERROR] Failed to save image to: {filename}. Check folder permissions.")
                numPictures += 1
                
            elif key == ord('g'):
                if status_dict["generating"]:
                    print('[System] Photogrammetry is already running')
                else:
                    print('[System] Spinning up Photogrammetry Thread...')
                    pg_thread = threading.Thread(target=run_photogrammetry, args=(status_dict,))
                    pg_thread.daemon = True
                    pg_thread.start()

        if not status_dict["generating"]:
            pg_thread = threading.Thread(target=run_photogrammetry, args=(status_dict,))
            pg_thread.daemon = True
            pg_thread.start()

        time.sleep(0.5)

        while status_dict["generating"]:
            time.sleep(2) 

        if status_dict.get("failed", False):
            raise RuntimeError("Photogrammetry stage failed")

        print("\n[System] Photogrammetry test complete! Check your local output/ folder.")
        interrupt_event.set()

    except KeyboardInterrupt:
        print("\n[System] User-initiated interrupt (Ctrl+C). Shutting down...")
    except Exception as e:
        print(f'[CRITICAL ERROR] {e}')
        sys.exit(1)
    finally:
        print("[System] Shutdown signaled. Terminating processes...")
        interrupt_event.set()
        
        for p in processes:
            if p.is_alive():
                p.terminate()
                p.join(timeout=1.0)

        if status_dict["generating"] and status_dict["pg_pid"]:
            print("[System] Terminating running photogrammetry binary context...")
            try:
                os.kill(status_dict["pg_pid"], 9)
            except ProcessLookupError:
                pass
        
        if pg_thread:
            pg_thread.join(timeout=1.0)

        print("[System] Releasing Shared Memory hooks...")
        for shm in shm_buffers:
            try:
                shm.close()
                shm.unlink()
            except Exception:
                pass

        cv2.destroyAllWindows()
        print("[System] Exit complete.\n")