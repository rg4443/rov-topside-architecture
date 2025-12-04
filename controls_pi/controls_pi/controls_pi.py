import rclpy
from control_msg.msg import ControllerInput
from rclpy.node import Node

class ControlsPI (Node):
    def __init__(self):
        super().__init__('controls_pi_node')
        self.subscriber = self.create_subscription(ControllerInput, 'controller_input', self.callback, 10)

    def callback(self, msg):
        self.get_logger().info(f'Left: ({msg.left_x}, {msg.left_y}), Right: ({msg.right_x}, {msg.right_y})')

def main():
    rclpy.init()
    node = ControlsPI()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        print()
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()
