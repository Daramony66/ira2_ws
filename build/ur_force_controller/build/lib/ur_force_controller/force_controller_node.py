#!/usr/bin/env python3
import time
from collections import deque

import rclpy
from rclpy.node import Node

from geometry_msgs.msg import WrenchStamped, PoseStamped
from std_msgs.msg import String, Bool
from std_srvs.srv import Trigger
from controller_manager_msgs.srv import SwitchController
from ur_msgs.srv import SetForceMode
from rcl_interfaces.msg import SetParametersResult


class ForceController(Node):
    def __init__(self):
        super().__init__('ur_force_controller')

        # =========================
        # Parameters
        # =========================
        self.declare_parameter('contact_threshold', 0)       # N (avg abs DEV)
        self.declare_parameter('contact_samples', 10)          # samples for avg
        self.declare_parameter('wrench_timeout', 2.0)          # seconds

        self.declare_parameter('force_target', 20.0)            # N (Active force)
        self.declare_parameter('force_max', 70.0)              # N (hard safety limit on RAW magnitude)
        self.declare_parameter('contact_lost_time', 120.0)     # seconds
        self.declare_parameter('contact_search_timeout', 120.0)

        # force mode config
        self.declare_parameter('task_frame', 'base')
        self.declare_parameter('force_mode_type', 2)           # 2 = NO_TRANSFORM (we use task_frame as-is)
        self.declare_parameter('force_sign', 1.0)              # 1.0 push, -1.0 pull

        self.declare_parameter('speed_limit_z', 0.50)          # m/s (applies to X)
        self.declare_parameter('damping_factor', 0.5)          # 0..1
        self.declare_parameter('gain_scaling', 2)            # 0..2
        self.declare_parameter('dev_limits', [2.0, 0.1, 0.1, 0.3, 0.3, 0.3])

        self.declare_parameter('zero_sensor_service_name', '/io_and_status_controller/zero_ftsensor')

        # ---- NEW: Bias/Zero gating parameters ----
        self.declare_parameter('settle_time_after_motion', 0.2)     # seconds to wait after motion_done before zero
        self.declare_parameter('bias_samples', 50)                  # how many samples to estimate bias
        self.declare_parameter('bias_std_threshold', 0.5)           # N, stability check
        self.declare_parameter('enable_software_bias', True)        # compute bias from stable samples
        self.declare_parameter('auto_zero_on_start', False)         # optional
        self.declare_parameter('scenario_mode', 0)                  # 0 = Maintain Force, 1 = Retreat on Target Reached

        # =========================
        # Load parameters
        # =========================
        self.contact_th = float(self.get_parameter('contact_threshold').value)
        self.n_contact = int(self.get_parameter('contact_samples').value)
        self.timeout_s = float(self.get_parameter('wrench_timeout').value)

        self.f_target = float(self.get_parameter('force_target').value)
        self.f_max = float(self.get_parameter('force_max').value)
        self.contact_lost_time = float(self.get_parameter('contact_lost_time').value)
        self.search_timeout = float(self.get_parameter('contact_search_timeout').value)

        self.task_frame_id = str(self.get_parameter('task_frame').value)
        self.force_mode_type = int(self.get_parameter('force_mode_type').value)
        self.force_side = float(self.get_parameter('force_sign').value)
        self.force_sign = self.force_side  # alias

        self.speed_limit_z = float(self.get_parameter('speed_limit_z').value)
        self.damping_factor = float(self.get_parameter('damping_factor').value)
        self.gain_scaling = float(self.get_parameter('gain_scaling').value)
        self.dev_limits = list(self.get_parameter('dev_limits').value)
        if len(self.dev_limits) != 6:
            self.dev_limits = [2.0, 0.1, 0.1, 0.3, 0.3, 0.3]

        self.zero_srv_name = str(self.get_parameter('zero_sensor_service_name').value)

        # NEW params
        self.settle_time = float(self.get_parameter('settle_time_after_motion').value)
        self.bias_samples = int(self.get_parameter('bias_samples').value)
        self.bias_std_th = float(self.get_parameter('bias_std_threshold').value)
        self.enable_sw_bias = bool(self.get_parameter('enable_software_bias').value)
        self.auto_zero_on_start = bool(self.get_parameter('auto_zero_on_start').value)
        self.scenario_mode = int(self.get_parameter('scenario_mode').value)

        # =========================
        # Current Task Frame (default identity)
        # =========================
        self.current_task_frame = PoseStamped()
        self.current_task_frame.header.frame_id = self.task_frame_id
        self.current_task_frame.pose.orientation.w = 1.0

        # =========================
        # State
        # =========================
        self.state = "WAIT_MOTION_DONE"
        self.state_enter_time = time.time()

        self.motion_done = False

        # Raw & dev force
        self.raw_mag = 0.0          # RAW magnitude from sensor
        self.fz = 0.0               # DEV magnitude (raw - bias), used for contact detection

        self.fz_hist = deque(maxlen=max(50, self.n_contact))
        self.last_wrench_time = time.time()

        self.last_contact_time = time.time()
        self.contact = False
        self.avg_abs = 0.0

        self.force_mode_active = False
        self.force_mode_request_pending = False

        # ---- NEW: bias learning gate ----
        self.bias_ready = False
        self.fz_bias = None
        self.bias_collecting = False
        self.bias_buf = deque(maxlen=max(10, self.bias_samples))
        self.timer_zero_delay = None

        # =========================
        # ROS Interfaces
        # =========================
        self.sub_wrench = self.create_subscription(
            WrenchStamped,
            '/force_torque_sensor_broadcaster/wrench',
            self.cb_wrench,
            50
        )

        self.sub_motion_done = self.create_subscription(
            Bool,
            '/motion_done',
            self.cb_motion_done,
            10
        )

        self.pub_state = self.create_publisher(String, '/force_state', 10)

        self.start_force_mode_cli = self.create_client(
            SetForceMode,
            '/force_mode_controller/start_force_mode'
        )
        self.stop_force_mode_cli = self.create_client(
            Trigger,
            '/force_mode_controller/stop_force_mode'
        )

        self.cli_zero_ftsensor = self.create_client(Trigger, self.zero_srv_name)

        self.cli_switch_controller = self.create_client(
            SwitchController,
            '/controller_manager/switch_controller'
        )

        self.sub_task_frame = self.create_subscription(
            PoseStamped,
            '/force_controller/target_frame',
            self.cb_task_frame,
            10
        )

        self.timer = self.create_timer(0.05, self.tick)
        self.add_on_set_parameters_callback(self.cb_parameters)

        self.get_logger().info("ForceController READY (waiting for /motion_done)")

        # Optional auto-zero on start (only if you want)
        if self.auto_zero_on_start:
            self.get_logger().warn("auto_zero_on_start=True: will zero & learn bias shortly after start.")
            self.timer_zero_delay = self.create_timer(1.0, self._auto_zero_once)

    # =========================
    # Helpers (Bias)
    # =========================
    def reset_contact_buffers(self):
        self.fz = 0.0
        self.raw_mag = 0.0
        self.avg_abs = 0.0
        self.contact = False
        self.fz_hist.clear()
        self.bias_buf.clear()
        self.last_contact_time = time.time()

    def start_bias_learning(self):
        """
        Start collecting stable RAW magnitude samples to estimate bias.
        Bias is only used if enable_software_bias=True.
        """
        self.bias_ready = False
        self.fz_bias = None
        self.bias_collecting = True
        self.bias_buf.clear()
        self.get_logger().info(
            f"Bias learning started: collecting {self.bias_samples} samples "
            f"(std_th={self.bias_std_th:.2f}N). Please keep robot still."
        )

    def try_finish_bias_learning(self):
        """
        If buffer full and stable -> set bias_ready.
        Stability check uses std threshold.
        """
        if not self.enable_sw_bias:
            # If disabled, consider bias ready with 0
            self.fz_bias = 0.0
            self.bias_ready = True
            self.bias_collecting = False
            return True

        if len(self.bias_buf) < self.bias_samples:
            return False

        # compute mean/std
        vals = list(self.bias_buf)[-self.bias_samples:]
        mean = sum(vals) / len(vals)
        var = sum((x - mean) ** 2 for x in vals) / len(vals)
        std = var ** 0.5

        if std <= self.bias_std_th:
            self.fz_bias = mean
            self.bias_ready = True
            self.bias_collecting = False
            self.fz_hist.clear()  # important: old samples useless now
            self.get_logger().info(f"Bias READY: {self.fz_bias:.2f} N (std={std:.2f} N)")
            return True

        # still moving/noisy -> keep sliding window
        self.get_logger().warn(f"Bias not stable yet (std={std:.2f}N > {self.bias_std_th:.2f}N). Keep still...")
        return False

    # =========================
    # Callbacks
    # =========================
    def cb_wrench(self, msg: WrenchStamped):
        fx = msg.wrench.force.x
        fy = msg.wrench.force.y
        fz = msg.wrench.force.z

        raw_force_mag = (fx**2 + fy**2 + fz**2)**0.5
        self.raw_mag = raw_force_mag
        self.last_wrench_time = time.time()

        # If we're learning bias, collect RAW magnitude (not dev)
        if self.bias_collecting:
            self.bias_buf.append(raw_force_mag)
            if self.try_finish_bias_learning():
                # once bias ready -> go to WAIT_CONTACT (if we are settling)
                if self.state == "SETTLING":
                    self.switch_to_force_controller()
                    self.set_state("WAIT_CONTACT")
            return

        # If bias not ready yet, ignore for contact (prevents wrong reference during motion)
        if not self.bias_ready:
            self.fz = 0.0
            return

        # Compute DEV magnitude for contact detection
        self.fz = raw_force_mag - float(self.fz_bias)
        self.fz_hist.append(self.fz)

    def cb_task_frame(self, msg: PoseStamped):
        self.current_task_frame = msg
        self.get_logger().info("Received NEW Task Frame (Vector aligned)")

    def cb_motion_done(self, msg: Bool):
        if msg.data and not self.motion_done:
            self.motion_done = True
            if self.state == "WAIT_MOTION_DONE":
                # Do NOT zero/learn bias immediately. Wait settle_time.
                self.reset_contact_buffers()
                self.set_state("SETTLING")

                # one-shot timer
                if self.timer_zero_delay is None:
                    self.timer_zero_delay = self.create_timer(self.settle_time, self._after_settle)

    def _auto_zero_once(self):
        if self.timer_zero_delay is not None:
            self.timer_zero_delay.cancel()
            self.timer_zero_delay = None
        self.reset_contact_buffers()
        self.set_state("SETTLING")
        self._after_settle()

    def _after_settle(self):
        # one-shot
        if self.timer_zero_delay is not None:
            self.timer_zero_delay.cancel()
            self.timer_zero_delay = None

        # Request hardware zero (tare)
        self.zero_sensor()

        # Start learning software bias AFTER zero request
        # (even if zero fails, bias learning still helps)
        self.start_bias_learning()

    # =========================
    # State handling
    # =========================
    def set_state(self, new_state: str):
        if new_state != self.state:
            self.state = new_state
            self.state_enter_time = time.time()
            self.get_logger().info(f"STATE -> {self.state}")

    # =========================
    # Force mode helpers
    # =========================
    def start_force_mode(self):
        if self.force_mode_active or self.force_mode_request_pending:
            return

        if not self.start_force_mode_cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().error("start_force_mode service not available (force_mode_controller inactive?)")
            return

        req = SetForceMode.Request()

        # Use the task frame we received from MotionManager (aligned to P1->P2)
        req.task_frame = self.current_task_frame
        req.type = 2  # NO_TRANSFORM

        # compliant in X only (aligned axis)
        req.selection_vector_x = True
        req.selection_vector_y = False
        req.selection_vector_z = False
        req.selection_vector_rx = False
        req.selection_vector_ry = False
        req.selection_vector_rz = False

        # target force along X
        req.wrench.force.x = float(self.f_target) * self.force_sign
        req.wrench.force.y = 0.0
        req.wrench.force.z = 0.0
        req.wrench.torque.x = 0.0
        req.wrench.torque.y = 0.0
        req.wrench.torque.z = 0.0

        # speed limit on compliant axis (X)
        req.speed_limits.linear.x = float(self.speed_limit_z)
        req.speed_limits.linear.y = 0.0
        req.speed_limits.linear.z = 0.0
        req.speed_limits.angular.x = 0.0
        req.speed_limits.angular.y = 0.0
        req.speed_limits.angular.z = 0.0

        req.deviation_limits = [float(x) for x in self.dev_limits]
        req.damping_factor = float(self.damping_factor)
        req.gain_scaling = float(self.gain_scaling)

        self.force_mode_request_pending = True
        future = self.start_force_mode_cli.call_async(req)
        future.add_done_callback(self._on_force_mode_started)

        q = req.task_frame.pose.orientation
        self.get_logger().info(
            f"Request FORCE MODE (Type={req.type}):\n"
            f"  Target Force X={req.wrench.force.x:.2f} N\n"
            f"  Task Frame Orient (xyzw)=[{q.x:.3f}, {q.y:.3f}, {q.z:.3f}, {q.w:.3f}]\n"
            f"  Selection X={req.selection_vector_x}"
        )

    def _on_force_mode_started(self, future):
        self.force_mode_request_pending = False
        try:
            resp = future.result()
            if resp.success:
                self.force_mode_active = True
                self.get_logger().info("Force mode ACTIVE")
            else:
                self.force_mode_active = False
                self.get_logger().error("Force mode rejected (controller not running or robot not ready)")
        except Exception as e:
            self.force_mode_active = False
            self.get_logger().error(f"Force mode exception: {e}")

    def stop_force_mode(self):
        if (not self.force_mode_active) and (not self.force_mode_request_pending):
            return

        if not self.stop_force_mode_cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().error("stop_force_mode service not available")
            self.force_mode_active = False
            self.force_mode_request_pending = False
            return

        req = Trigger.Request()
        self.stop_force_mode_cli.call_async(req)
        self.force_mode_active = False
        self.force_mode_request_pending = False
        self.get_logger().info("Force mode STOPPED")

        self.switch_to_motion_controller()

    def zero_sensor(self):
        """
        Call the zero_ftsensor service to tare the sensor.
        IMPORTANT: we don't learn bias here directly; we learn it after settle.
        """
        if not self.cli_zero_ftsensor.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn(f"Service {self.zero_srv_name} not available. Cannot zero sensor.")
            return

        self.get_logger().info("Calling zero_ftsensor...")
        req = Trigger.Request()
        future = self.cli_zero_ftsensor.call_async(req)
        future.add_done_callback(self._on_zero_done)

    def _on_zero_done(self, future):
        try:
            resp = future.result()
            if resp.success:
                self.get_logger().info("Sensor zeroed successfully.")
            else:
                self.get_logger().warn(f"Sensor zero failed: {resp.message}")
        except Exception as e:
            self.get_logger().error(f"Sensor zero exception: {e}")

    def switch_to_force_controller(self):
        self.call_switch_controller(
            start_controllers=['force_mode_controller'],
            stop_controllers=['scaled_joint_trajectory_controller']
        )

    def switch_to_motion_controller(self):
        self.call_switch_controller(
            start_controllers=['scaled_joint_trajectory_controller'],
            stop_controllers=['force_mode_controller']
        )

    def call_switch_controller(self, start_controllers, stop_controllers):
        if not self.cli_switch_controller.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn("switch_controller service not available. Skipping auto-switch.")
            return

        req = SwitchController.Request()
        req.activate_controllers = start_controllers
        req.deactivate_controllers = stop_controllers
        req.strictness = SwitchController.Request.BEST_EFFORT
        future = self.cli_switch_controller.call_async(req)
        future.add_done_callback(
            lambda f: self.get_logger().info(f"Switched controllers: +{start_controllers} -{stop_controllers}")
        )

    # =========================
    # Main loop
    # =========================
    def tick(self):
        now = time.time()

        # 0) wrench timeout safety (only after bias ready and after settling)
        if self.state not in ("WAIT_MOTION_DONE", "SETTLING") and self.bias_ready:
            if (now - self.last_wrench_time) > self.timeout_s:
                self.set_state("ABORT_TIMEOUT")
                self.stop_force_mode()

        # 1) compute contact (avg abs of DEV)
        self.contact = False
        self.avg_abs = 0.0
        if self.bias_ready and len(self.fz_hist) >= self.n_contact:
            last_n = list(self.fz_hist)[-self.n_contact:]
            self.avg_abs = sum(abs(x) for x in last_n) / float(self.n_contact)
            self.contact = self.avg_abs >= self.contact_th

        if self.contact:
            self.last_contact_time = now

        # 2) state machine
        if self.state == "WAIT_MOTION_DONE":
            pass

        elif self.state == "SETTLING":
            # Wait here until bias becomes ready (cb_wrench will move to WAIT_CONTACT)
            pass

        elif self.state == "WAIT_CONTACT":
            if (now - self.state_enter_time) > self.search_timeout:
                self.get_logger().error("Contact search TIMEOUT")
                self.set_state("ABORT_SEARCH_TIMEOUT")
                return

            if self.contact:
                self.set_state("FORCE_HOLD")

        elif self.state == "FORCE_HOLD":
            # start force mode once
            if self.contact and not self.force_mode_active:
                self.start_force_mode()

            # hard safety on RAW magnitude
            if self.raw_mag > self.f_max:
                self.get_logger().error("FORCE LIMIT EXCEEDED (RAW magnitude)")
                self.stop_force_mode()
                self.set_state("ABORT_FORCE_LIMIT")

            # SCENARIO 1: Retreat immediately if target force reached
            # We check if dev force (fz) is close to target (f_target)
            # Use abs() because sign depends on direction, but usually we care about magnitude reaching target
            if self.scenario_mode == 1 and self.force_mode_active:
                # Check if we reached 95% of target force
                # fz is deviation, f_target is goal.
                # If we are pulling (-), fz is negative.
                current_force_val = abs(self.fz)
                target_force_val = abs(self.f_target)
                
                if current_force_val >= (0.95 * target_force_val):
                    self.get_logger().info(f"Scenario 1: Target force reached ({current_force_val:.2f}N). Retreating FAST (Punch)...")
                    self.stop_force_mode()
                    self.set_state("RETRACT_FAST")

            # contact lost -> retract
            if (now - self.last_contact_time) > self.contact_lost_time:
                self.stop_force_mode()
                self.set_state("RETRACT")

        elif self.state == "RETRACT":
            pass

        elif self.state.startswith("ABORT"):
            self.stop_force_mode()

        # 3) publish state message
        msg = String()
        msg.data = (
            f"{self.state} | RAW={self.raw_mag:.2f}N | DEV={self.fz:.2f}N | avg|DEV|={self.avg_abs:.2f}N | "
            f"bias={'NA' if self.fz_bias is None else f'{self.fz_bias:.2f}'} | "
            f"target={self.f_target:.2f}N | force_mode={'ON' if self.force_mode_active else 'OFF'}"
        )
        self.pub_state.publish(msg)

        return SetParametersResult(successful=True)

    def cb_parameters(self, params):
        for p in params:
            if p.name == 'force_target':
                if p.type_ == rclpy.parameter.Parameter.Type.DOUBLE:
                    self.f_target = p.value
                    self.get_logger().info(f"Updated force_target to {self.f_target} N")

                    if self.force_mode_active:
                        self.get_logger().info("Updating active force command...")
                        self.start_force_mode()

        return SetParametersResult(successful=True)


def main():
    rclpy.init()
    node = ForceController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()