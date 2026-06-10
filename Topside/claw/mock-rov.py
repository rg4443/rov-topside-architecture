import time
from pymavlink import mavutil

print("starting mov rov sim")
rov = mavutil.mavlink_connection('udpout:127.0.0.1:14550', source_system=1)

button_state = 0.0

try:
    while True:
        rov.mav.heartbeat_send(
            mavutil.mavlink.MsAV_TYPE_SUB,
            mavutil.mavlink.MAV_AUTOPILOT_ARDUPILOTMEGA,
            0, 0, 0
        )
        print("heartbeat sent")
        
        button_state = 1.0 if button_state == 0.0 else 0.0
        
        name_bytes = b"custom_1" + b"\x00" * (10 - len("custom_1"))
        
        rov.mav.named_value_float_send(
            time_boot_ms=int(time.time() * 1000) & 0xFFFFFFFF,
            name=name_bytes,
            value=button_state
        )
        print(f"injected button message, custom_1: {button_state}")
        
        time.sleep(3)

except KeyboardInterrupt:
    print("mock rov stopped via user intervention.")