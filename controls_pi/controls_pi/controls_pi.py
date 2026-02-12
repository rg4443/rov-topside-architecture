import rclpy
from control_msg.msg import ControllerInput
from rclpy.node import Node
from pymavlink import mavutil
from pymavlink.dialects.v20 import common as mavlink_common
import RPi.GPIO as GPIO
import serial
import time
from math import *
from time import perf_counter
import XConfigMap

BAUD_RATE = 115200
PORT = "/dev/ttyACM0"
last_update = time.perf_counter()
MAX_MSG_DELAY = 0.1
INIT_WAIT = 2
DEBUG = False

def constructMessage(data:list) -> str:
    payload = ""
    for i in range(len(data)):
        payload += str(data[i])
        if (i != len(data) - 1):
            payload += ","

    checksum_val = 0
    for c in payload:
        checksum_val ^= ord(c)
    checksum = str(hex(checksum_val)).upper().removeprefix("0X")

    msg = "$" + payload + "*" + checksum + "\n"
    return msg

class ControlsPI (Node):
    def __init__(self):
        super().__init__('controls_pi_node')
        self.pin = 18
        self.update_flag = False
        self.subscriber = self.create_subscription(ControllerInput, 'controller_input', self.callback, 10)
        self.mapping = XConfigMap.ROVMapping(1)
        self.ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
        self.ser.reset_input_buffer()
        self.ser.reset_output_buffer()
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.pin, GPIO.OUT)
        time.sleep(INIT_WAIT)
        self.timer = self.create_timer(MAX_MSG_DELAY, self.sendMsg)
        print("Ready!")

    def sendMsg(self):
        global last_update
        if self.update_flag:
            msg = constructMessage(self.mapping.data)
            self.ser.write(msg.encode("utf-8"))
            if DEBUG:
                print("Writing " + msg)
            self.ser.flush()
            self.update_flag = False
            last_update = time.perf_counter()
        else:
            curr = time.perf_counter()
            if curr - last_update > MAX_MSG_DELAY:
                self.mapping.update()
                msg = constructMessage(self.mapping.data)
                self.ser.write(msg.encode("utf-8"))
                if DEBUG:
                    print("Writing " + msg)
                self.ser.flush()
                last_update = curr


    def destroy_node(self):
        msg = constructMessage([128, 128, 128, 128, 128, 128, 128, 128, 128, 1])
        self.ser.write(msg.encode("utf-8"))
        self.ser.flush()
        self.ser.close()

        GPIO.output(self.pin, 1)
        GPIO.cleanup()
        super().destroy_node()

    def callback(self, msg):
        self.mapping.ProcessEventCallback(msg)
        self.update_flag = True
        self.sendMsg()

        GPIO.output(self.pin, 1-msg.a)
    
def main():
    rclpy.init()

    try:
        node = ControlsPI()
        rclpy.spin(node)
    except KeyboardInterrupt:
        print()
    finally:
        try:
            node.destroy_node()
        except Exception:
            pass
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()
