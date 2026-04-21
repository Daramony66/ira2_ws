# Library
import rclpy
from rclpy.node import Node

from haptic_teleop.srv import AppControlService
from haptic_teleop.srv import ContactPointService
from haptic_teleop.srv import SystemStateService
from haptic_teleop.msg import StartMove

from geometry_msgs.msg import Point

# Class
class UnityBridgeNode(Node):

    def __init__(self, external_callback=None):
        super().__init__('unity_bridge')

        self.cp = Point()
        self.on_move_changed = external_callback

        # create service clients
        self.app_control_client = self.create_client(AppControlService, 'app_control')
        self.contact_point_client = self.create_client(ContactPointService, 'cp_position')
        self.state_client = self.create_client(SystemStateService, 'system_state')
        
        # create subscriber
        self.move_subscriber = self.create_subscription(StartMove, 'start_move', self.start_move_callback, 10)

        # wait for services
        while not self.app_control_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn('Waiting for Unity services...')

        while not self.contact_point_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn('Waiting for Unity services...')

        while not self.state_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn('Waiting for Unity services...')
    
    # --------------------------------------------------------------
    
    def change_state(self, state_id):
        # state_id: 
        # 0 = pre-calibration, 
        # 1 = calibration, 
        # 2 = punch
        # 3 = push
        
        req = SystemStateService.Request()
        req.command = state_id

        future = self.state_client.call_async(req)
        future.add_done_callback(self.callback_change_state)


    def callback_change_state(self, future):
        response = future.result()

        if response.success:
            self.get_logger().info('State changed successfully')
        else:
            self.get_logger().error('Failed to change state')
            
    # --------------------------------------------------------------
    
    def change_mode(self, mode_id):
        # mode_id:
        # 0 = play / replay
        # 1 = stop
        
        req = AppControlService.Request()
        req.command = mode_id

        future = self.app_control_client.call_async(req)
        future.add_done_callback(self.callback_change_mode)

    def callback_change_mode(self, future):
        response = future.result()

        if response.success:
            self.get_logger().info('Mode changed successfully')
        else:
            self.get_logger().error('Failed to change mode')
    
    # --------------------------------------------------------------
    
    def request_contact_point(self):
        req = ContactPointService.Request()
        req.command = 0

        future = self.contact_point_client.call_async(req)
        future.add_done_callback(self.callback_contact_point)

    def callback_contact_point(self, future):
        response = future.result()

        if not response.success:
            return

        self.cp = response.position
        self.get_logger().info(f"CP: {self.cp.x}, {self.cp.y}, {self.cp.z}")
        
    # --------------------------------------------------------------
    
    def start_move_callback(self, msg):
        self.get_logger().info(f"Received start_move = {msg.start}")
        
        if msg.start and self.on_move_changed:
            self.on_move_changed(msg.start)
    
    # --------------------------------------------------------------
    
def main():
    rclpy.init()

    node = UnityBridgeNode()

    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()