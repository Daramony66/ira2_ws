#!/usr/bin/env python3

import sys
import os
import yaml
import rclpy
from rclpy.node import Node
from rclpy.duration import Duration
from geometry_msgs.msg import TransformStamped, Pose
from tf2_ros import TransformListener, Buffer

# Ajouté le 12/03 à 18h04
from std_msgs.msg import Bool
from controller_manager_msgs.srv import SwitchController


from sensor_msgs.msg import JointState

class TeachNode(Node):
    def __init__(self):
        super().__init__('teach_node')
        
        # TF Buffer
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        
        # Joint State Listener
        self.current_joints = None
        self.sub_joints = self.create_subscription(
            JointState,
            '/joint_states',
            self.cb_joints,
            10
        )
        
        self.points = {}
        self.output_file = os.path.join(
            os.getcwd(), 'points.yaml'
        )
        self.get_logger().info(f"Teach Node Ready. Points will be saved to: {self.output_file}")

        # Ajouté le 12/03 à 18h04

        # Freedrive publisher
        self.freedrive_pub = self.create_publisher(
            Bool,
            '/freedrive_mode_controller/enable_freedrive_mode',
            10
        )

        # Controller switch client
        self.switch_cli = self.create_client(
            SwitchController,
            '/controller_manager/switch_controller'
        )

        # Freedrive timer
        self.freedrive_timer = None



        
    def cb_joints(self, msg):
        # We need to ensure we map them correctly. The order in msg might differ from controller expectation
        # But usually for UR it is consistent. We just save what we get, but ideally map to names.
        # We'll save a dict of {name: pos} or just the list if we trust order.
        # Best to save dict {name: pos} and reconstruct list later.
        self.current_joints = dict(zip(msg.name, msg.position))

    def get_current_pose(self):
        try:
            # Look up transform from base to tool0
            now = rclpy.time.Time()
            trans = self.tf_buffer.lookup_transform(
                'base',
                'tool0',
                now,
                timeout=Duration(seconds=1.0)
            )
            
            p = [
                trans.transform.translation.x,
                trans.transform.translation.y,
                trans.transform.translation.z
            ]
            q = [
                trans.transform.rotation.x,
                trans.transform.rotation.y,
                trans.transform.rotation.z,
                trans.transform.rotation.w
            ]
            return p, q
            
        except Exception as e:
            self.get_logger().error(f"Could not get transform: {e}")
            return None, None

    def save_points(self):
        with open(self.output_file, 'w') as f:
            yaml.dump(self.points, f)
        self.get_logger().info(f"Points saved to {self.output_file}")



    # Ajouté le 12/03 à 18h29

    def start_freedrive(self):
        self.get_logger().info("Waiting for switch_controller service...")
        if not self.switch_cli.wait_for_service(timeout_sec=5.0):
            self.get_logger().error("switch_controller service not available!")
            return
        req = SwitchController.Request()
        req.activate_controllers = ['freedrive_mode_controller']
        req.deactivate_controllers = ['scaled_joint_trajectory_controller']
        req.strictness = 2
        self.switch_cli.call_async(req)
        import time; time.sleep(0.5)
        self.freedrive_timer = self.create_timer(0.1, self._pub_freedrive)

    def stop_freedrive(self):
        if self.freedrive_timer:
            self.freedrive_timer.cancel()
        req = SwitchController.Request()
        req.activate_controllers = ['scaled_joint_trajectory_controller']
        req.deactivate_controllers = ['freedrive_mode_controller']
        req.strictness = 2
        self.switch_cli.call_async(req)

    def _pub_freedrive(self):
        msg = Bool()
        msg.data = True
        self.freedrive_pub.publish(msg)
    
    
    
    def run_interactive(self):
        print("-------------------------------------------------")

        self.start_freedrive() #Ajouté le 12/03 à 18h07

        print("TEACH MODE")
        print("1. Move robot to P1 (Start Point)")
        print("   Press [ENTER] to record P1")
        input()
        
        p1_pos, p1_rot = self.get_current_pose()
        
        # Joints
        if self.current_joints is None:
             print("Error: No joint states received yet!")
             return
        p1_joints = self.current_joints.copy()
        
        if p1_pos:
            self.points['p1'] = {'pos': p1_pos, 'rot': p1_rot, 'joints': p1_joints}
            print(f"Recorded P1: {p1_pos}")
        else:
            print("Failed to record P1 (TF Error)")
            return

        print("2. Move robot to P2 (Direction Point)")
        print("   Press [ENTER] to record P2")
        input()
        
        p2_pos, p2_rot = self.get_current_pose()
        if p2_pos:
            self.points['p2'] = {'pos': p2_pos, 'rot': p2_rot}
            print(f"Recorded P2: {p2_pos}")
        else:
            print("Failed to record P2 (TF Error)")
            return
            
        self.save_points()

        self.stop_freedrive() #Ajouté le 12/03 à 18h07

        print("Done. You can now close this node.")

def main():
    rclpy.init()
    node = TeachNode()
    
    # Spin in a separate thread not strictly needed for this simple blocking input script
    # but we need spin_once to update TF buffer
    
    # We'll just spin_once inside the interactive loop calls effectively 
    # or better: run interactions in main thread, background thread for spinning?
    # Simpler: Call spin_once() before get_current_pose() in a loop to ensure buffer is full?
    # No, TF listener is async. We need a Spinner.
    
    import threading
    spinner = threading.Thread(target=rclpy.spin, args=(node,), daemon=True)
    spinner.start()
    
    try:
        node.run_interactive()
    except KeyboardInterrupt:
        pass
    #finally:
        #rclpy.shutdown()
    
    #Ajouté le 12/03 à 18h30
    finally:
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()
