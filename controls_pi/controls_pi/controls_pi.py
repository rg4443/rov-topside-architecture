import rclpy
from control_msg.msg import ControllerInput
from rclpy.node import Node
from pymavlink import mavutil
from pymavlink.dialects.v20 import common as mavlink_common
import RPi.GPIO as GPIO
import pigpio

class ControlsPI (Node):
    def __init__(self):
        super().__init__('controls_pi_node')
        self.pin = 18
        self.subscriber = self.create_subscription(ControllerInput, 'controller_input', self.callback, 10)
        self.target = 1
        self.connection = None
        self.connect()
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.pin, GPIO.OUT)

    def destroy_node(self):
        self.close()
        GPIO.output(self.pin, 1)
        super().destroy_node()

    def close(self):
        try:
            self.connection.close()
        except Exception:
            pass
        self.connection = None

    def callback(self, msg):
        x = round(msg.left_y * 1000)
        y = round(msg.left_x * 1000)
        z = round(msg.right_y * 1000)
        yaw = round(msg.right_x * 1000)
        pitch = 0
        roll = round((msg.left_trigger - msg.right_trigger) * 500)

        buttons = 0
        buttons += int(msg.a) << 0
        buttons += int(msg.b) << 1
        buttons += int(msg.x) << 2
        buttons += int(msg.y) << 3
        buttons += int(msg.left_bumper) << 4
        buttons += int(msg.right_bumper) << 5
        buttons += int(msg.back) << 6
        buttons += int(msg.start) << 7
        buttons += int(msg.left_stick_pressed) << 8
        buttons += int(msg.right_stick_pressed) << 9
        buttons += int(msg.left_trigger > 0.5) << 10
        buttons += int(msg.right_trigger > 0.5) << 11
        buttons += int(msg.dpad_up) << 12
        buttons += int(msg.dpad_down) << 13
        buttons += int(msg.dpad_left) << 14
        buttons += int(msg.dpad_right) << 15

        self.send_message(x, y, z, roll, pitch, yaw, buttons)

        GPIO.output(self.pin, 1-msg.a)
    
    def connect(self):
        try:
            # TODO: Change connection string
            self.connection = mavutil.mavlink_connection('udpout:127.0.0.1:14550')
            try:
                self.connection.wait_heartbeat(timeout=5)
                self.target = self.connection.target_system
            except Exception:
                self.get_logger().error('Failed to receive heartbeat from MAVLink.')
                self.close()
        except Exception:
            self.get_logger().error('Failed to establish MAVLink connection.')

    def send_message(self, x, y, z, roll, pitch, yaw, buttons):
        if self.connection is None or self.connection.mav is None:
            self.connect()
            if self.connection is None or self.connection.mav is None:
                return
        message = mavlink_common.MAVLink_manual_control_message(
            self.target, x, y, z, yaw, buttons,
            buttons2 = 0, enabled_extensions = 3, s = pitch, t = roll)
        try:
            self.connection.mav.send(message)
        except Exception:
            self.get_logger().error('MAVLink disconnected. Reconnecting...')
            self.close()
            self.connect()

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
