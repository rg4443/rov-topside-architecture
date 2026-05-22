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

IMAGE_FOLDER = os.path.abspath("images")
OUTPUT_FOLDER = os.path.abspath("output")
CACHE_FOLDER = os.path.abspath("cache")

ENABLE_LOGGING = True
FRAME_SHAPE = (1080, 1920, 3)
FRAME_SIZE_BYTES = np.prod(FRAME_SHAPE) * np.dtype(np.uint8).itemsize

def init_folders():
    os.makedirs(CACHE_FOLDER, exist_ok=True)
    for p in (IMAGE_FOLDER, OUTPUT_FOLDER):
        if os.path.exists(p):
            try:
                shutil.rmtree(p)
            except Exception as e:
                print(f"Failed to remove {p}: {e}")
        os.makedirs(p, exist_ok=True)


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

def run_photogrammetry(status_dict):
    status_dict["generating"] = True
    base_path = os.path.dirname(os.path.abspath(__file__))
    tool_path = os.path.join(base_path, "capture_tool")
    output_file = os.path.join(OUTPUT_FOLDER, "model.usdz")

    if not os.path.isfile(tool_path):
        print(f"[ERROR] Could not find compiled swift tool at: {tool_path}.")
        status_dict["generating"] = False
        return

    cmd = [tool_path, IMAGE_FOLDER, output_file]

    with open("photogrammetry.log", "w") as logfile:
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, bufsize=1)
        status_dict["pg_pid"] = proc.pid
        
        for line in proc.stdout:
            print(line, end="")      
            logfile.write(line)      
        ret = proc.wait()

    if ret == 0:
        print(f"[System] PHOTOGRAMMETRY FINISHED. Saved to: {output_file}")
    else:
        print(f"[System] Photogrammetry exited with code {ret}")
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
    status_dict = manager.dict({"generating": False, "pg_pid": None})
    
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
    print("[System] Controls: 'p' = Take Picture | 'g' = Start Photogrammetry | 'q' = Quit")

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
                success = cv2.imwrite(filename, ai_view, [int(cv2.IMWRITE_JPEG_QUALITY), 100])
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

    except KeyboardInterrupt:
        print("\n[System] User-initiated interrupt (Ctrl+C). Shutting down...")
    except Exception as e:
        print(f'[CRITICAL ERROR] {e}')
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