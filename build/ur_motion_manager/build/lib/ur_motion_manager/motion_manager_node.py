#!/usr/bin/env python3

#Ajouté le 13/03 à 17h11
import rtde_receive


import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

from std_msgs.msg import String, Bool
from std_srvs.srv import Trigger
from geometry_msgs.msg import PoseStamped
from controller_manager_msgs.srv import SwitchController
from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint
import math


# Imports for vector math
import os
import yaml
import threading
import numpy as np
from scipy.spatial.transform import Rotation as R

def calculate_orientation_vector(p1, p2):
    # Vector from P1 to P2
    v = np.array(p2) - np.array(p1)
    norm = np.linalg.norm(v)
    if norm < 1e-6:
        return None  # Points are too close
    
    # Normalize X-axis (force direction is now X)
    x_axis = v / norm
    
    # Create arbitrary Y-axis
    world_z = np.array([0, 0, 1])
    
    # If X is parallel to World Z, choose World Y
    if np.abs(np.dot(x_axis, world_z)) > 0.99:
        temp_y = np.array([0, 1, 0])
    else:
        temp_y = np.cross(world_z, x_axis)
        
    y_axis = temp_y / np.linalg.norm(temp_y)
    z_axis = np.cross(x_axis, y_axis)
    
    # Rotation matrix [x_axis, y_axis, z_axis]
    rot_matrix = np.column_stack((x_axis, y_axis, z_axis))
    
    # Convert to quaternion
    r = R.from_matrix(rot_matrix)
    quat = r.as_quat() # (x, y, z, w)
    return quat



class MotionManager(Node):
    def __init__(self):
        super().__init__('ur_motion_manager')

        self.publisher_script = self.create_publisher(String, '/urscript_interface/script_command', 10)

        # =========================
        # Internal state
        # =========================
        self.current_force_state = "UNKNOWN"
        self.goal_active = False
        self.abort_active = False

        # We will publish motion_done after APPROACH finishes
        self.approach_sent = False
        self.approach_done = False

        # =========================
        # Action client (passthrough REQUIRED)
        # =========================
        self.trajectory_client = ActionClient(
            self,
            FollowJointTrajectory,
            '/scaled_joint_trajectory_controller/follow_joint_trajectory'
        )

        # =========================
        # ROS interfaces
        # =========================
        self.sub_force_state = self.create_subscription(
            String,
            '/force_state',
            self.cb_force_state,
            10
        )

        self.sub_abort = self.create_subscription(
            String,
            '/safety_abort',
            self.cb_abort,
            10
        )

        # Publish a dedicated "motion done" signal (do NOT publish to /force_state)
        self.pub_motion_done = self.create_publisher(
            Bool,
            '/motion_done',
            10
        )

        # NEW: Listen for Cartesian targets
        self.sub_target_pose = self.create_subscription(
            PoseStamped,
            '/motion_manager/target_pose',
            self.cb_target_pose,
            10
        )
        
        self.pub_force_frame = self.create_publisher(
            PoseStamped,
            '/force_controller/target_frame',
            10
        )

        # Controller Switcher
        self.cli_switch_controller = self.create_client(
            SwitchController,
            '/controller_manager/switch_controller'
        )

        #Ajouté le 13/03 à 17h12
        self.tcp_speed = [0.0]*6
        self._start_rtde_thread()
        self.display_timer = self.create_timer(0.5, self.display_status)

        self.get_logger().info("MotionManager READY (Waiting for target_pose)")

        # Load points if available
        self.p1 = None
        self.p2 = None
        self.load_points()

        # Start APPROACH immediately? NO, wait for user.
        # But per requirements: "When nodes start... goes to P1"
        # We'll wait a brief moment for connections then go? 
        # Or better, trigger via a simple timer or wait for user confirmation?
        # User said: "When nodes start... robot goes to P1"
        # So we auto-start.
        
        if self.p1 is not None and self.p2 is not None:
             self.get_logger().info("Found P1/P2. Starting Auto-Sequence in 2s...")
             # Timer to allow other nodes to spin up
             self.timer_auto = self.create_timer(2.0, self.auto_start_sequence)
        
    def load_points(self):
        try:
            # Assuming points.yaml in current working dir or specific path
            # We will use the same path as teach_node: current working dir
            # Or better, package share? For now, CWD or fixed path
             # Try a few locations
            paths = [
                'points.yaml',
                os.path.join(os.getcwd(), 'points.yaml'),
                #'/home/stlab24-04/ur3e_ws/src/ur_motion_manager/ur_motion_manager/points.yaml'
                '/home/stlab24-04/ira2_ws/src/ur_motion_manager/ur_motion_manager/points.yaml'
            ]
            
            data = None
            for p in paths:
                if os.path.exists(p):
                    with open(p, 'r') as f:
                        data = yaml.safe_load(f)
                    self.get_logger().info(f"Loaded points from {p}")
                    break
            
            if data:
                self.p1 = data['p1']['pos']
                self.p2 = data['p2']['pos']
                
                if 'joints' in data['p1']:
                     # Convert dict back to list if needed, or keeping as dict
                     # The message listener saved it as a dict {name: pos}
                     self.p1_joints = data['p1']['joints']
                else:
                     self.p1_joints = None
                     self.get_logger().warn("No joint states found in points.yaml for P1")

        except Exception as e:
            self.get_logger().error(f"Failed to load points: {e}")

    def auto_start_sequence(self):
        self.timer_auto.cancel()
        
        # Ensure scaled_joint_trajectory_controller is ACTIVE before moving
        # We also ensure force_mode_controller is STOPPED
        self.activate_motion_controller()
        
        # Then send motion (maybe give a small delay for switch?)
        # call_async callback will trigger move? Or just wait a bit.
        # simpler: loop check or one-shot timer.
        self.timer_start_move = self.create_timer(1.0, self.send_approach_motion_p1)

    def activate_motion_controller(self):
        if not self.cli_switch_controller.wait_for_service(timeout_sec=1.0):
             self.get_logger().warn("switch_controller not available")
             return
             
        req = SwitchController.Request()
        req.activate_controllers = ['scaled_joint_trajectory_controller']
        req.deactivate_controllers = ['force_mode_controller', 'passthrough_trajectory_controller', 'forward_position_controller']
        req.strictness = SwitchController.Request.BEST_EFFORT
        self.future_switch = self.cli_switch_controller.call_async(req)
        self.get_logger().info("Requesting activation of scaled_joint_trajectory_controller...")


    # =========================
    # Callbacks
    # =========================
    def cb_abort(self, msg: String):
        self.abort_active = True
        self.get_logger().error(f"EMERGENCY STOP received: {msg.data}")

    def cb_force_state(self, msg: String):
        if self.abort_active:
            return

        state = msg.data.split('|')[0].strip()

        if state != self.current_force_state:
            self.current_force_state = state
            # self.get_logger().info(f"Force state -> {state}")
            self.handle_state_change(state)

    def cb_target_pose(self, msg: PoseStamped):
        self.get_logger().info("Received Target Pose. Sending URScript movel()...")
        # Extract x,y,z, rx, ry, rz
        # Extract x,y,z, rx, ry, rz
        # We need to convert Quat to Axis-Angle (Rotation Vector) for URScript p[x,y,z,ax,ay,az]
        
        # Using scipy for robust conversion
        from scipy.spatial.transform import Rotation as R
        
        p = msg.pose.position
        q = msg.pose.orientation

        # Create rotation object from quaternion (x,y,z,w)
        # Note: Scipy expects scalar-last (x, y, z, w) for 'xyzw' format?
        # Scipy uses (x, y, z, w) by default.
        rot = R.from_quat([q.x, q.y, q.z, q.w])
        
        # Convert to rotation vector (angle * axis) which UR uses
        rot_vec = rot.as_rotvec()
        rx, ry, rz = rot_vec
            
        # Using movej is safer for approach as it avoids linear path singularities
        # movel requires a feasible straight line, movej just needs a feasible end pose.
        # Reducing speed to 0.1 for safety
        cmd = f"movej(p[{p.x},{p.y},{p.z},{rx},{ry},{rz}], a=0.1, v=0.1)"
        self.get_logger().info(f"Sending URScript: {cmd}")
        
        smsg = String()
        smsg.data = cmd
        self.publisher_script.publish(smsg)
        
        # We simulate approach_done logic
        # Ideally we monitor execution, but URScript is fire-and-forget unless we monitor feedback.
        # Let's assume successful start and after a short delay we say motion done?
        # A better way is to rely on force_controller seeing "WAIT_MOTION_DONE" -> "motion_done"
        # But force_controller waits for /motion_done.
        # So we should publish /motion_done = True after some time?
        # Or let the USER confirm?
        # Let's automate it by just publishing success after a fixed time for now (simulating "Done")
        # OR we just rely on the script finishing.
        # For this prototype, I will publish motion_done after 5 seconds to initiate force mode.
        import threading
        t = threading.Timer(2.0, self._publish_motion_done)
        t.start()
        
    def _publish_motion_done(self):
        if hasattr(self, 'timer_frame_pub'):
            self.timer_frame_pub.cancel()
            
        msg = Bool()
        msg.data = True
        self.pub_motion_done.publish(msg)
        self.get_logger().info("Published /motion_done (Assuming move complete)")

    def stop_trajectory_controller(self):
        if not self.cli_switch_controller.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn("switch_controller service not available. Cannot stop trajectory controller.")
            return

        # We deactivate the trajectory controller to ensure the driver accepts script commands without contention
        req = SwitchController.Request()
        req.deactivate_controllers = ['scaled_joint_trajectory_controller']
        req.strictness = SwitchController.Request.BEST_EFFORT
        future = self.cli_switch_controller.call_async(req)
        # We don't wait for result to block, just hope it's fast enough or allows the script to pass

    # =========================
    # Motion decision logic
    # =========================
    def handle_state_change(self, state: str):
        # Don’t send anything while a goal is active
        if self.goal_active:
            return

        # AFTER force phase ends, ForceController should publish RETRACT
        if state == "RETRACT":
            self.send_retract_motion()
        
        elif state == "RETRACT_FAST":
            self.send_retract_motion_fast()

        # Optional: if ForceController ever re-requests APPROACH (rare)
        elif state == "APPROACH" and not self.approach_sent:
            self.send_approach_motion()

    # =========================
    # Trajectories
    # =========================
    def send_approach_motion_p1(self):
        # Cancel the timer so this isn't called again!
        if hasattr(self, 'timer_start_move') and self.timer_start_move is not None:
             self.timer_start_move.cancel()
             self.timer_start_move = None

        if self.goal_active or self.abort_active:
            return

        if self.approach_sent:
             # Already sent, do not resend
             return

        if self.p1 is None:
            self.get_logger().error("Cannot approach P1: Not loaded")
            return

        self.approach_sent = True
        self.get_logger().info(f"Moving to P1 (Joints via Trajectory Controller)")
        
        # 1. Calculate and publish Force Frame (P1->P2)
        quat_force = calculate_orientation_vector(self.p1, self.p2)
        if quat_force is None:
             self.get_logger().error("P1 and P2 too close!")
             # We might still move, but force control will fail?
        else:
             # Start publishing the frame immediately and loop it
             self.frame_data = (self.p1, quat_force)
             self.timer_frame_pub = self.create_timer(0.2, self._pub_frame_cb) 

        # 2. Execute Motion using Trajectory Controller (Robost to singularities and controller conflicts)
        if not hasattr(self, 'p1_joints') or self.p1_joints is None:
             self.get_logger().error("Cannot move: P1 joints not loaded!")
             return

        goal = FollowJointTrajectory.Goal()
        # Ensure we use the standard order. 
        # Usually: shoulder_pan, shoulder_lift, elbow, wrist_1, wrist_2, wrist_3
        # But we should rely on the names we saved or the standard list.
        joint_names = [
            'shoulder_pan_joint',
            'shoulder_lift_joint',
            'elbow_joint',
            'wrist_1_joint',
            'wrist_2_joint',
            'wrist_3_joint'
        ]
        goal.trajectory.joint_names = joint_names
        
        point = JointTrajectoryPoint()
        # Map from our saved dict to the list order
        try:
            positions = []
            for name in joint_names:
                positions.append(self.p1_joints[name])
            point.positions = positions
        except KeyError as e:
            self.get_logger().error(f"Missing joint in saved data: {e}")
            return
            
        point.time_from_start.sec = 2 # Allow 2 seconds for move
        goal.trajectory.points.append(point)
        
        self.send_goal(goal, goal_name="APPROACH")
        
        # Note regarding 'motion_done':
        # The 'send_goal' method already has a callback `result_cb` which sets `self.approach_done = True`
        # and publishes `/motion_done`.
        # So we do NOT need a timer here anymore! The action client handles it.

    def _pub_frame_cb(self):
        if hasattr(self, 'frame_data'):
            self.publish_force_frame(*self.frame_data)
        
    def publish_force_frame(self, pos, quat):
        msg = PoseStamped()
        msg.header.frame_id = "base"
        msg.header.stamp = self.get_clock().now().to_msg()
        
        msg.pose.position.x = float(pos[0])
        msg.pose.position.y = float(pos[1])
        msg.pose.position.z = float(pos[2])
        
        msg.pose.orientation.x = quat[0]
        msg.pose.orientation.y = quat[1]
        msg.pose.orientation.z = quat[2]
        msg.pose.orientation.w = quat[3]
        
        self.pub_force_frame.publish(msg)
        # self.get_logger().info("Published Target Force Frame") # Too noisy if looped

    def send_approach_motion(self):
        # Default behavior if P1 not valid or legacy
        if self.p1 is not None:
             self.send_approach_motion_p1()
             return
             
        if self.goal_active or self.abort_active or self.approach_sent:
            return

        self.approach_sent = True
        self.get_logger().info("Sending APPROACH trajectory (Joints)")

        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = [
            'shoulder_pan_joint',
            'shoulder_lift_joint',
            'elbow_joint',
            'wrist_1_joint',
            'wrist_2_joint',
            'wrist_3_joint'
        ]

        point = JointTrajectoryPoint()
        point.positions = [
            0.293,   # shoulder_pan
           -0.949,   # shoulder_lift
            1.077,   # elbow
           -1.669,   # wrist_1
           -1.631,   # wrist_2
            0.0005    # wrist_3
        ]
        point.time_from_start.sec = 3

        goal.trajectory.points.append(point)
        self.send_goal(goal, goal_name="APPROACH")

    def send_retract_motion(self):
        if self.goal_active or self.abort_active:
            return

        self.get_logger().info("Sending RETRACT trajectory")

        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = [
            'shoulder_pan_joint',
            'shoulder_lift_joint',
            'elbow_joint',
            'wrist_1_joint',
            'wrist_2_joint',
            'wrist_3_joint'
        ]

        # Use P1 for retreat if available
        if hasattr(self, 'p1_joints') and self.p1_joints is not None:
             self.get_logger().info("Retreating to P1...")
             point = JointTrajectoryPoint()
             try:
                positions = []
                for name in goal.trajectory.joint_names:
                    positions.append(self.p1_joints[name])
                point.positions = positions
             except KeyError as e:
                self.get_logger().error(f"Missing joint in saved data during retract: {e}")
                # Fallback to hardcoded
                point = JointTrajectoryPoint()
                point.positions = [0.30, -1.20, 1.20, -1.20, -1.57, 0.00]
        else:
            # Fallback
            self.get_logger().warn("P1 not known for retreat! Using hardcoded fallback.")
            point = JointTrajectoryPoint()
            point.positions = [
                0.30,
                -1.20,
                1.20,
                -1.20,
                -1.57,
                0.00
            ]
        
        point.time_from_start.sec = 4  # Slower retreat

        goal.trajectory.points.append(point)
        self.send_goal(goal, goal_name="RETRACT")

    def send_retract_motion_fast(self):
        # We need a small delay to ensure controller switch (Force -> Position) is complete
        # otherwise the trajectory controller sees the deadline as 'now' and demands infinite velocity.
        self.get_logger().info("Scheduling FAST RETRACT (Punch) in 0.5s...")
        self.timer_retract = self.create_timer(0.5, self._execute_retract_fast)

    def _execute_retract_fast(self):
        if self.timer_retract:
            self.timer_retract.cancel()
            self.timer_retract = None

        if self.goal_active or self.abort_active:
            return

        self.get_logger().info("Executing FAST RETRACT trajectory NOW")

        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = [
            'shoulder_pan_joint',
            'shoulder_lift_joint',
            'elbow_joint',
            'wrist_1_joint',
            'wrist_2_joint',
            'wrist_3_joint'
        ]

        # Use P1 for retreat if available
        if hasattr(self, 'p1_joints') and self.p1_joints is not None:
             point = JointTrajectoryPoint()
             try:
                positions = []
                for name in goal.trajectory.joint_names:
                    positions.append(self.p1_joints[name])
                point.positions = positions
             except KeyError as e:
                self.get_logger().error(f"Missing joint: {e}")
                # Fallback to hardcoded
                point = JointTrajectoryPoint()
                point.positions = [0.30, -1.20, 1.20, -1.20, -1.57, 0.00]
        else:
            # Fallback
            point = JointTrajectoryPoint()
            point.positions = [0.30, -1.20, 1.20, -1.20, -1.57, 0.00]
        
        # VERY FAST RETREAT (0.5 seconds)
        point.time_from_start.nanosec = 500000000 # 0.5s
        point.time_from_start.sec = 0

        goal.trajectory.points.append(point)
        self.send_goal(goal, goal_name="RETRACT_FAST")

    # =========================
    # Action handling
    # =========================
    def send_goal(self, goal, goal_name: str):
        self.goal_active = True
        self.current_goal_name = goal_name

        self.trajectory_client.wait_for_server()
        future = self.trajectory_client.send_goal_async(goal)
        future.add_done_callback(self.goal_response_cb)

    def goal_response_cb(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.goal_active = False
            self.get_logger().error(f"Trajectory rejected ({self.current_goal_name})")
            return

        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.result_cb)

    def result_cb(self, future):
        _ = future.result()  # not used, but forces completion
        self.goal_active = False
        self.get_logger().info(f"Trajectory completed ({self.current_goal_name})")

        # If APPROACH finished → publish /motion_done = True ONCE
        if self.current_goal_name == "APPROACH" and not self.approach_done:
            self.approach_done = True
            
            # Stop publishing the force frame now that we are done moving
            if hasattr(self, 'timer_frame_pub') and self.timer_frame_pub is not None:
                self.timer_frame_pub.cancel()
                self.timer_frame_pub = None
            
            msg = Bool()
            msg.data = True
            self.pub_motion_done.publish(msg)
            self.get_logger().info("Published /motion_done = True")

        # If RETRACT finished you can also publish motion_done False (optional)
        # (Usually not needed)
        # if self.current_goal_name == "RETRACT":
        #     msg = Bool(); msg.data = False
        #     self.pub_motion_done.publish(msg)


    #Ajouté le 13/03 à 17h13
    def _start_rtde_thread(self):
        def loop():
            r = rtde_receive.RTDEReceiveInterface('192.168.1.101')
            while rclpy.ok():
                self.tcp_speed = r.getActualTCPSpeed()
        t = threading.Thread(target=loop, daemon=True)
        t.start()

    def display_status(self):
        v = self.tcp_speed
        # print(f"[TCP SPEED] vx={v[0]:.4f} vy={v[1]:.4f} vz={v[2]:.4f} m/s")


def main():
    rclpy.init()
    node = MotionManager()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

# # VERSION DU 08/04 à 11h15

# #!/usr/bin/env python3

# #Ajouté le 13/03 à 17h11
# import rtde_receive
# import rtde_control as rtde_ctrl #Ajouté le 08/04 à 11h15
# from ur_dashboard_msgs.msg import SafetyMode #Ajouté le 08/04 à 11h50

# import time #Ajouté le 08/04 à 11h15


# import rclpy
# from rclpy.node import Node
# from rclpy.action import ActionClient

# from std_msgs.msg import String, Bool
# from std_srvs.srv import Trigger
# from geometry_msgs.msg import PoseStamped
# from controller_manager_msgs.srv import SwitchController
# from control_msgs.action import FollowJointTrajectory
# from trajectory_msgs.msg import JointTrajectoryPoint
# import math


# # Imports for vector math
# import os
# import yaml
# import threading
# import numpy as np
# from scipy.spatial.transform import Rotation as R

# def calculate_orientation_vector(p1, p2):
#     # Vector from P1 to P2
#     v = np.array(p2) - np.array(p1)
#     norm = np.linalg.norm(v)
#     if norm < 1e-6:
#         return None  # Points are too close
    
#     # Normalize X-axis (force direction is now X)
#     x_axis = v / norm
    
#     # Create arbitrary Y-axis
#     world_z = np.array([0, 0, 1])
    
#     # If X is parallel to World Z, choose World Y
#     if np.abs(np.dot(x_axis, world_z)) > 0.99:
#         temp_y = np.array([0, 1, 0])
#     else:
#         temp_y = np.cross(world_z, x_axis)
        
#     y_axis = temp_y / np.linalg.norm(temp_y)
#     z_axis = np.cross(x_axis, y_axis)
    
#     # Rotation matrix [x_axis, y_axis, z_axis]
#     rot_matrix = np.column_stack((x_axis, y_axis, z_axis))
    
#     # Convert to quaternion
#     r = R.from_matrix(rot_matrix)
#     quat = r.as_quat() # (x, y, z, w)
#     return quat



# class MotionManager(Node):
#     def __init__(self):
#         super().__init__('ur_motion_manager')

#         self.publisher_script = self.create_publisher(String, '/urscript_interface/script_command', 10)

#         # =========================
#         # Internal state
#         # =========================
#         self.current_force_state = "UNKNOWN"
#         self.goal_active = False
#         self.abort_active = False

#         # We will publish motion_done after APPROACH finishes
#         self.approach_sent = False
#         self.approach_done = False

#         # =========================
#         # Action client (passthrough REQUIRED)
#         # =========================
#         self.trajectory_client = ActionClient(
#             self,
#             FollowJointTrajectory,
#             '/scaled_joint_trajectory_controller/follow_joint_trajectory'
#         )

#         # =========================
#         # ROS interfaces
#         # =========================
#         self.sub_force_state = self.create_subscription(
#             String,
#             '/force_state',
#             self.cb_force_state,
#             10
#         )

#         self.sub_abort = self.create_subscription(
#             String,
#             '/safety_abort',
#             self.cb_abort,
#             10
#         )

#         # Publish a dedicated "motion done" signal (do NOT publish to /force_state)
#         self.pub_motion_done = self.create_publisher(
#             Bool,
#             '/motion_done',
#             10
#         )

#         # NEW: Listen for Cartesian targets
#         self.sub_target_pose = self.create_subscription(
#             PoseStamped,
#             '/motion_manager/target_pose',
#             self.cb_target_pose,
#             10
#         )
        
#         self.pub_force_frame = self.create_publisher(
#             PoseStamped,
#             '/force_controller/target_frame',
#             10
#         )

#         # Controller Switcher
#         self.cli_switch_controller = self.create_client(
#             SwitchController,
#             '/controller_manager/switch_controller'
#         )

#         #Ajouté le 08/04 à 11h50
#         self.sub_safety = self.create_subscription(
#             SafetyMode,
#             '/io_and_status_controller/safety_mode',
#             self.cb_safety_mode,
#             10
#         )

#         self.protective_stop_detected = False #Ajouté le 08/04 à 11h50

#         #Ajouté le 13/03 à 17h12
#         self.tcp_speed = [0.0]*6
#         self._start_rtde_thread()
#         #self.rtde_ctrl = rtde_ctrl.RTDEControlInterface('192.168.1.101') #Ajouté le 08/04 à 11h15 #Commenté à 11h30
#         self.display_timer = self.create_timer(0.5, self.display_status)

#         self.get_logger().info("MotionManager READY (Waiting for target_pose)")

#         # Load points if available
#         self.p1 = None
#         self.p2 = None
#         self.load_points()

#         # Start APPROACH immediately? NO, wait for user.
#         # But per requirements: "When nodes start... goes to P1"
#         # We'll wait a brief moment for connections then go? 
#         # Or better, trigger via a simple timer or wait for user confirmation?
#         # User said: "When nodes start... robot goes to P1"
#         # So we auto-start.
        
#         if self.p1 is not None and self.p2 is not None:
#              self.get_logger().info("Found P1/P2. Starting Auto-Sequence in 2s...")
#              # Timer to allow other nodes to spin up
#              self.timer_auto = self.create_timer(2.0, self.auto_start_sequence)
        
#     def load_points(self):
#         try:
#             # Assuming points.yaml in current working dir or specific path
#             # We will use the same path as teach_node: current working dir
#             # Or better, package share? For now, CWD or fixed path
#              # Try a few locations
#             paths = [
#                 'points.yaml',
#                 os.path.join(os.getcwd(), 'points.yaml'),
#                 #'/home/stlab24-04/ur3e_ws/src/ur_motion_manager/ur_motion_manager/points.yaml'
#                 '/home/stlab24-04/ira2_ws/src/ur_motion_manager/ur_motion_manager/points.yaml'
#             ]
            
#             data = None
#             for p in paths:
#                 if os.path.exists(p):
#                     with open(p, 'r') as f:
#                         data = yaml.safe_load(f)
#                     self.get_logger().info(f"Loaded points from {p}")
#                     break
            
#             if data:
#                 self.p1 = data['p1']['pos']
#                 self.p2 = data['p2']['pos']
                
#                 if 'joints' in data['p1']:
#                      # Convert dict back to list if needed, or keeping as dict
#                      # The message listener saved it as a dict {name: pos}
#                      self.p1_joints = data['p1']['joints']
#                 else:
#                      self.p1_joints = None
#                      self.get_logger().warn("No joint states found in points.yaml for P1")

#         except Exception as e:
#             self.get_logger().error(f"Failed to load points: {e}")

#     def auto_start_sequence(self):
#         self.timer_auto.cancel()
        
#         # Ensure scaled_joint_trajectory_controller is ACTIVE before moving
#         # We also ensure force_mode_controller is STOPPED
#         self.activate_motion_controller()
        
#         # Then send motion (maybe give a small delay for switch?)
#         # call_async callback will trigger move? Or just wait a bit.
#         # simpler: loop check or one-shot timer.
#         self.timer_start_move = self.create_timer(1.0, self.send_approach_motion_p1)

#     def activate_motion_controller(self):
#         if not self.cli_switch_controller.wait_for_service(timeout_sec=1.0):
#              self.get_logger().warn("switch_controller not available")
#              return
             
#         req = SwitchController.Request()
#         req.activate_controllers = ['scaled_joint_trajectory_controller']
#         req.deactivate_controllers = ['force_mode_controller', 'passthrough_trajectory_controller', 'forward_position_controller']
#         req.strictness = SwitchController.Request.BEST_EFFORT
#         self.future_switch = self.cli_switch_controller.call_async(req)
#         self.get_logger().info("Requesting activation of scaled_joint_trajectory_controller...")


#     # =========================
#     # Callbacks
#     # =========================
#     def cb_abort(self, msg: String):
#         self.abort_active = True
#         self.get_logger().error(f"EMERGENCY STOP received: {msg.data}")

#     def cb_force_state(self, msg: String):
#         if self.abort_active:
#             return

#         state = msg.data.split('|')[0].strip()

#         if state != self.current_force_state:
#             self.current_force_state = state
#             # self.get_logger().info(f"Force state -> {state}")
#             self.handle_state_change(state)

#     def cb_target_pose(self, msg: PoseStamped):
#         self.get_logger().info("Received Target Pose. Sending URScript movel()...")
#         # Extract x,y,z, rx, ry, rz
#         # Extract x,y,z, rx, ry, rz
#         # We need to convert Quat to Axis-Angle (Rotation Vector) for URScript p[x,y,z,ax,ay,az]
        
#         # Using scipy for robust conversion
#         from scipy.spatial.transform import Rotation as R
        
#         p = msg.pose.position
#         q = msg.pose.orientation

#         # Create rotation object from quaternion (x,y,z,w)
#         # Note: Scipy expects scalar-last (x, y, z, w) for 'xyzw' format?
#         # Scipy uses (x, y, z, w) by default.
#         rot = R.from_quat([q.x, q.y, q.z, q.w])
        
#         # Convert to rotation vector (angle * axis) which UR uses
#         rot_vec = rot.as_rotvec()
#         rx, ry, rz = rot_vec
            
#         # Using movej is safer for approach as it avoids linear path singularities
#         # movel requires a feasible straight line, movej just needs a feasible end pose.
#         # Reducing speed to 0.1 for safety
#         cmd = f"movej(p[{p.x},{p.y},{p.z},{rx},{ry},{rz}], a=0.1, v=0.1)"
#         self.get_logger().info(f"Sending URScript: {cmd}")
        
#         smsg = String()
#         smsg.data = cmd
#         self.publisher_script.publish(smsg)
        
#         # We simulate approach_done logic
#         # Ideally we monitor execution, but URScript is fire-and-forget unless we monitor feedback.
#         # Let's assume successful start and after a short delay we say motion done?
#         # A better way is to rely on force_controller seeing "WAIT_MOTION_DONE" -> "motion_done"
#         # But force_controller waits for /motion_done.
#         # So we should publish /motion_done = True after some time?
#         # Or let the USER confirm?
#         # Let's automate it by just publishing success after a fixed time for now (simulating "Done")
#         # OR we just rely on the script finishing.
#         # For this prototype, I will publish motion_done after 5 seconds to initiate force mode.
#         import threading
#         t = threading.Timer(2.0, self._publish_motion_done)
#         t.start()
        
#     def _publish_motion_done(self):
#         if hasattr(self, 'timer_frame_pub'):
#             self.timer_frame_pub.cancel()
            
#         msg = Bool()
#         msg.data = True
#         self.pub_motion_done.publish(msg)
#         self.get_logger().info("Published /motion_done (Assuming move complete)")

#     def stop_trajectory_controller(self):
#         if not self.cli_switch_controller.wait_for_service(timeout_sec=1.0):
#             self.get_logger().warn("switch_controller service not available. Cannot stop trajectory controller.")
#             return

#         # We deactivate the trajectory controller to ensure the driver accepts script commands without contention
#         req = SwitchController.Request()
#         req.deactivate_controllers = ['scaled_joint_trajectory_controller']
#         req.strictness = SwitchController.Request.BEST_EFFORT
#         future = self.cli_switch_controller.call_async(req)
#         # We don't wait for result to block, just hope it's fast enough or allows the script to pass

#     # =========================
#     # Motion decision logic
#     # =========================
#     def handle_state_change(self, state: str):
#         # Don’t send anything while a goal is active
#         if self.goal_active:
#             return

#         # AFTER force phase ends, ForceController should publish RETRACT
#         if state == "RETRACT":
#             self.send_retract_motion()
        
#         elif state == "RETRACT_FAST":
#             self.send_retract_motion_fast()

#         # Optional: if ForceController ever re-requests APPROACH (rare)
#         elif state == "APPROACH" and not self.approach_sent:
#             self.send_approach_motion()

#     # =========================
#     # Trajectories
#     # =========================
#     def send_approach_motion_p1(self):
#         # Cancel the timer so this isn't called again!
#         if hasattr(self, 'timer_start_move') and self.timer_start_move is not None:
#              self.timer_start_move.cancel()
#              self.timer_start_move = None

#         if self.goal_active or self.abort_active:
#             return

#         if self.approach_sent:
#              # Already sent, do not resend
#              return

#         if self.p1 is None:
#             self.get_logger().error("Cannot approach P1: Not loaded")
#             return

#         self.approach_sent = True
#         self.get_logger().info(f"Moving to P1 (Joints via Trajectory Controller)")
        
#         # 1. Calculate and publish Force Frame (P1->P2)
#         quat_force = calculate_orientation_vector(self.p1, self.p2)
#         if quat_force is None:
#              self.get_logger().error("P1 and P2 too close!")
#              # We might still move, but force control will fail?
#         else:
#              # Start publishing the frame immediately and loop it
#              self.frame_data = (self.p1, quat_force)
#              self.timer_frame_pub = self.create_timer(0.2, self._pub_frame_cb) 

#         # 2. Execute Motion using Trajectory Controller (Robost to singularities and controller conflicts)
#         if not hasattr(self, 'p1_joints') or self.p1_joints is None:
#              self.get_logger().error("Cannot move: P1 joints not loaded!")
#              return

#         goal = FollowJointTrajectory.Goal()
#         # Ensure we use the standard order. 
#         # Usually: shoulder_pan, shoulder_lift, elbow, wrist_1, wrist_2, wrist_3
#         # But we should rely on the names we saved or the standard list.
#         joint_names = [
#             'shoulder_pan_joint',
#             'shoulder_lift_joint',
#             'elbow_joint',
#             'wrist_1_joint',
#             'wrist_2_joint',
#             'wrist_3_joint'
#         ]
#         goal.trajectory.joint_names = joint_names
        
#         point = JointTrajectoryPoint()
#         # Map from our saved dict to the list order
#         try:
#             positions = []
#             for name in joint_names:
#                 positions.append(self.p1_joints[name])
#             point.positions = positions
#         except KeyError as e:
#             self.get_logger().error(f"Missing joint in saved data: {e}")
#             return
            
#         point.time_from_start.sec = 2 # Allow 2 seconds for move
#         goal.trajectory.points.append(point)
        
#         self.send_goal(goal, goal_name="APPROACH")
        
#         # Note regarding 'motion_done':
#         # The 'send_goal' method already has a callback `result_cb` which sets `self.approach_done = True`
#         # and publishes `/motion_done`.
#         # So we do NOT need a timer here anymore! The action client handles it.

#     def _pub_frame_cb(self):
#         if hasattr(self, 'frame_data'):
#             self.publish_force_frame(*self.frame_data)
        
#     def publish_force_frame(self, pos, quat):
#         msg = PoseStamped()
#         msg.header.frame_id = "base"
#         msg.header.stamp = self.get_clock().now().to_msg()
        
#         msg.pose.position.x = float(pos[0])
#         msg.pose.position.y = float(pos[1])
#         msg.pose.position.z = float(pos[2])
        
#         msg.pose.orientation.x = quat[0]
#         msg.pose.orientation.y = quat[1]
#         msg.pose.orientation.z = quat[2]
#         msg.pose.orientation.w = quat[3]
        
#         self.pub_force_frame.publish(msg)
#         # self.get_logger().info("Published Target Force Frame") # Too noisy if looped

#     def send_approach_motion(self):
#         # Default behavior if P1 not valid or legacy
#         if self.p1 is not None:
#              self.send_approach_motion_p1()
#              return
             
#         if self.goal_active or self.abort_active or self.approach_sent:
#             return

#         self.approach_sent = True
#         self.get_logger().info("Sending APPROACH trajectory (Joints)")

#         goal = FollowJointTrajectory.Goal()
#         goal.trajectory.joint_names = [
#             'shoulder_pan_joint',
#             'shoulder_lift_joint',
#             'elbow_joint',
#             'wrist_1_joint',
#             'wrist_2_joint',
#             'wrist_3_joint'
#         ]

#         point = JointTrajectoryPoint()
#         point.positions = [
#             0.293,   # shoulder_pan
#            -0.949,   # shoulder_lift
#             1.077,   # elbow
#            -1.669,   # wrist_1
#            -1.631,   # wrist_2
#             0.0005    # wrist_3
#         ]
#         point.time_from_start.sec = 3

#         goal.trajectory.points.append(point)
#         self.send_goal(goal, goal_name="APPROACH")

#     def send_retract_motion(self):
#         if self.goal_active or self.abort_active:
#             return

#         self.get_logger().info("Sending RETRACT trajectory")

#         goal = FollowJointTrajectory.Goal()
#         goal.trajectory.joint_names = [
#             'shoulder_pan_joint',
#             'shoulder_lift_joint',
#             'elbow_joint',
#             'wrist_1_joint',
#             'wrist_2_joint',
#             'wrist_3_joint'
#         ]

#         # Use P1 for retreat if available
#         if hasattr(self, 'p1_joints') and self.p1_joints is not None:
#              self.get_logger().info("Retreating to P1...")
#              point = JointTrajectoryPoint()
#              try:
#                 positions = []
#                 for name in goal.trajectory.joint_names:
#                     positions.append(self.p1_joints[name])
#                 point.positions = positions
#              except KeyError as e:
#                 self.get_logger().error(f"Missing joint in saved data during retract: {e}")
#                 # Fallback to hardcoded
#                 point = JointTrajectoryPoint()
#                 point.positions = [0.30, -1.20, 1.20, -1.20, -1.57, 0.00]
#         else:
#             # Fallback
#             self.get_logger().warn("P1 not known for retreat! Using hardcoded fallback.")
#             point = JointTrajectoryPoint()
#             point.positions = [
#                 0.30,
#                 -1.20,
#                 1.20,
#                 -1.20,
#                 -1.57,
#                 0.00
#             ]
        
#         point.time_from_start.sec = 4  # Slower retreat

#         goal.trajectory.points.append(point)
#         self.send_goal(goal, goal_name="RETRACT")

#     def send_retract_motion_fast(self):
#         # We need a small delay to ensure controller switch (Force -> Position) is complete
#         # otherwise the trajectory controller sees the deadline as 'now' and demands infinite velocity.
#         self.get_logger().info("Scheduling FAST RETRACT (Punch) in 0.5s...")
#         self.timer_retract = self.create_timer(0.5, self._execute_retract_fast)

#     def _execute_retract_fast(self):
#         if self.timer_retract:
#             self.timer_retract.cancel()
#             self.timer_retract = None

#         if self.goal_active or self.abort_active:
#             return

#         self.get_logger().info("Executing FAST RETRACT trajectory NOW")

#         goal = FollowJointTrajectory.Goal()
#         goal.trajectory.joint_names = [
#             'shoulder_pan_joint',
#             'shoulder_lift_joint',
#             'elbow_joint',
#             'wrist_1_joint',
#             'wrist_2_joint',
#             'wrist_3_joint'
#         ]

#         # Use P1 for retreat if available
#         if hasattr(self, 'p1_joints') and self.p1_joints is not None:
#              point = JointTrajectoryPoint()
#              try:
#                 positions = []
#                 for name in goal.trajectory.joint_names:
#                     positions.append(self.p1_joints[name])
#                 point.positions = positions
#              except KeyError as e:
#                 self.get_logger().error(f"Missing joint: {e}")
#                 # Fallback to hardcoded
#                 point = JointTrajectoryPoint()
#                 point.positions = [0.30, -1.20, 1.20, -1.20, -1.57, 0.00]
#         else:
#             # Fallback
#             point = JointTrajectoryPoint()
#             point.positions = [0.30, -1.20, 1.20, -1.20, -1.57, 0.00]
        
#         # VERY FAST RETREAT (0.5 seconds)
#         point.time_from_start.nanosec = 500000000 # 0.5s
#         point.time_from_start.sec = 0

#         goal.trajectory.points.append(point)
#         self.send_goal(goal, goal_name="RETRACT_FAST")

#     # =========================
#     # Action handling
#     # =========================
#     def send_goal(self, goal, goal_name: str):
#         self.goal_active = True
#         self.current_goal_name = goal_name

#         self.trajectory_client.wait_for_server()
#         future = self.trajectory_client.send_goal_async(goal)
#         future.add_done_callback(self.goal_response_cb)

#     def goal_response_cb(self, future):
#         goal_handle = future.result()
#         if not goal_handle.accepted:
#             self.goal_active = False
#             self.get_logger().error(f"Trajectory rejected ({self.current_goal_name})")
#             return

#         result_future = goal_handle.get_result_async()
#         result_future.add_done_callback(self.result_cb)

#     def result_cb(self, future):
#         _ = future.result()  # not used, but forces completion
#         self.goal_active = False
#         self.get_logger().info(f"Trajectory completed ({self.current_goal_name})")

#         # If APPROACH finished → publish /motion_done = True ONCE
#         if self.current_goal_name == "APPROACH" and not self.approach_done:
#             self.approach_done = True
            
#             # Stop publishing the force frame now that we are done moving
#             if hasattr(self, 'timer_frame_pub') and self.timer_frame_pub is not None:
#                 self.timer_frame_pub.cancel()
#                 self.timer_frame_pub = None
            
#             msg = Bool()
#             msg.data = True
#             self.pub_motion_done.publish(msg)
#             self.get_logger().info("Published /motion_done = True")

#         # If RETRACT finished you can also publish motion_done False (optional)
#         # (Usually not needed)
#         # if self.current_goal_name == "RETRACT":
#         #     msg = Bool(); msg.data = False
#         #     self.pub_motion_done.publish(msg)


#     #Ajouté le 13/03 à 17h13
#     def _start_rtde_thread(self):
#         def loop():
#             r = rtde_receive.RTDEReceiveInterface('192.168.1.101')
#             while rclpy.ok():
#                 self.tcp_speed = r.getActualTCPSpeed()
#         t = threading.Thread(target=loop, daemon=True)
#         t.start()

#     def display_status(self):
#         v = self.tcp_speed
#         #print(f"[TCP SPEED] vx={v[0]:.4f} vy={v[1]:.4f} vz={v[2]:.4f} m/s") #Commenté le 08/04 à 11h30

#     #Ajouté le 08/04 à 11h50
#     def cb_safety_mode(self, msg):
#         if msg.mode == SafetyMode.PROTECTIVE_STOP:
#             self.get_logger().error("PROTECTIVE STOP détecté — relance automatique...")
#             self.protective_stop_detected = True
#             raise SystemExit("PROTECTIVE_STOP")

# # Commenté le 08/04 à 11h15
# # def main():
# #     rclpy.init()
# #     node = MotionManager()
# #     rclpy.spin(node)
# #     node.destroy_node()
# #     rclpy.shutdown()

# # Ajouté le 08/04 à 11h15
# def main():
#     rclpy.init()
#     while rclpy.ok():
#         try:
#             node = MotionManager()
#             rclpy.spin(node)
#             break
#         #except Exception as e: #Commenté le 08/04 à 11h50
#         except (Exception, SystemExit) as e: #Ajouté le 08/04 à 11h50
#             print(f"Echec: {e} — relance dans 3s...")
#             #Commenté le 08/04 à 11h55
#             # try:
#             #     print("Reupload script...")
#             #     r = rtde_ctrl.RTDEControlInterface('192.168.1.101')
#             #     r.reuploadScript()
#             #     print("Reupload OK !")

#             #Ajouté le 08/04 à 11h55
#             reupload_ok = False
#             while not reupload_ok:
#                 try:
#                     print("Reupload script...")
#                     r = rtde_ctrl.RTDEControlInterface('192.168.1.101')
#                     r.reuploadScript()
#                     print("Reupload OK !")
#                     reupload_ok = True
#                 except Exception as e2:
#                     print(f"Reupload echoue, nouvel essai dans 2s: {e2}")
#                     time.sleep(2)

#             #Commenté le 08/04 à 11h55
#             # except Exception as e2:
#             #     print(f"Reupload echoue: {e2}")
#             for i in range(3, 0, -1):
#                 print(f"Relance dans {i}s...")
#                 time.sleep(1)
#     rclpy.shutdown()

# if __name__ == '__main__':
#     main()