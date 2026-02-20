import rclpy
from control_msg.msg import ControllerInput
from rclpy.node import Node
from pymavlink import mavutil
from pymavlink.dialects.v20 import common as mavlink_common
import RPi.GPIO as GPIO
import pigpio
import time

class ControlsPI (Node):
    def __init__(self):
        super().__init__('controls_pi_node')
        self.pin = 18
        self.subscriber = self.create_subscription(ControllerInput, 'controller_input', self.callback, 10)
        self.target = 1
        self.lastMessage = 0
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
        # Try to send a stop message if it didn't crash
        try:
            message = mavlink_common.MAVLink_manual_control_message(self.target, 0, 0, 500, 0, 0)
            self.connection.mav.send(message)
        except Exception:
            pass
        # Close the connection
        try:
            self.connection.close()
        except Exception:
            pass
        self.connection = None

    def callback(self, msg):
        x = round(msg.left_y * 1000)
        y = round(msg.left_x * 1000)
        z = round(msg.right_y * 500) + 500
        yaw = round(msg.right_x * 1000)
        pitch = 0
        roll = round((msg.left_trigger - msg.right_trigger) * 250) + 500

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
            print('Connecting to MAVLink...')
            for port in range(10):
                try:
                    self.connection = mavutil.mavlink_connection(f'/dev/ttyACM{port}', baud=115200)
                    break
                except Exception:
                    pass
            try:
                self.connection.wait_heartbeat(timeout=5)
                self.target = self.connection.target_system
                self.get_logger().info(f'Received heartbeat. Target: {self.target}.')
                if not self.connection.motors_armed():
                    print('Arming motors...')
                    self.connection.mav.command_long_send(
                        self.target, self.connection.target_component,
                        mavutil.mavlink.MAV_CMD_COMPONENT_ARM_DISARM,
                        0,
                        1,  # 1 = arm, 0 = disarm
                        0, 0, 0, 0, 0, 0)
                    self.connection.motors_armed_wait()
                    self.get_logger().info('Motors armed.')
                else:
                    self.get_logger().info('Motors already armed.')
                self.lastMessage = time.time()
            except Exception as e:
                self.get_logger().error(f'Connection failed. Error: {e}')
                self.close()
        except Exception as e:
            self.get_logger().error(f'Failed to establish MAVLink connection. Error: {e}')

    def send_message(self, x, y, z, roll, pitch, yaw, buttons):
        if self.connection is None or self.connection.mav is None:
            self.connect()
            if self.connection is None or self.connection.mav is None:
                return
        currentTime = time.time()
        try:
            while self.connection.recv_match(blocking=False) is not None:
                self.lastMessage = currentTime
        except Exception as e:
            pass
        if (currentTime - self.lastMessage) > 2.0:
            self.get_logger().warning('MAVLink connection lost. Reconnecting...')
            self.close()
            self.connect()
        message = mavlink_common.MAVLink_manual_control_message(
            self.target, x, y, z, yaw, buttons)
            #buttons2 = 0, enabled_extensions = 3, s = pitch, t = roll)
        try:
            self.connection.mav.send(message)
            self.get_logger().info(str(message))
        except Exception as e:
            self.get_logger().error(f'MAVLink disconnected. Reconnecting... Error: {e}')
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
