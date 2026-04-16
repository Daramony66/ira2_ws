#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import WrenchStamped
import time
import math

class SafetyMonitor(Node):
    def __init__(self):
        super().__init__('ur_safety_monitor')

        # =========================
        # Parameters
        # =========================
        # We set a hard limit (e.g. 100N) that is higher than the operational limit (e.g. 50N)
        # This acts as a "circuit breaker"
        self.declare_parameter('max_force_allowed', 80.0)    # Newton (Absolute Max)
        self.declare_parameter('watchdog_timeout', 0.5)      # seconds (Max silence from sensor)

        self.max_force = float(self.get_parameter('max_force_allowed').value)
        self.watchdog_timeout = float(self.get_parameter('watchdog_timeout').value)

        # =========================
        # Internal state
        # =========================
        # =========================
        # Internal state
        # =========================
        self.node_start_time = time.time()
        self.last_msg_time = time.time()
        self.abort_triggered = False
        
        # Bias for zeroing (simple startup bias)
        self.fz_bias = None
        self.bias_samples = []

        # =========================
        # ROS interfaces
        # =========================
        # Listen to RAW sensor data (Independent source)
        # Use SensorDataQoS for best effort compatibility
        from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=50
        )
        self.sub_wrench = self.create_subscription(
            WrenchStamped,
            '/force_torque_sensor_broadcaster/wrench',
            self.cb_wrench,
            qos_profile
        )

        self.pub_abort = self.create_publisher(
            String,
            '/safety_abort',
            10
        )

        # High frequency check (50Hz)
        self.timer = self.create_timer(0.02, self.tick)

        self.get_logger().info(f"SafetyMonitor INDEPENDENT MODE. Max Force={self.max_force}N")

    # =========================
    # Callbacks
    # =========================
    def cb_wrench(self, msg: WrenchStamped):
        self.last_msg_time = time.time()
        
        if self.abort_triggered:
            return

        fx = msg.wrench.force.x
        fy = msg.wrench.force.y
        fz = msg.wrench.force.z
        
        # Calculate Magnitude (Independent of orientation)
        mag = math.sqrt(fx**2 + fy**2 + fz**2)
        
        # Simple startup bias logic (Auto-tare on startup)
        if self.fz_bias is None:
            if len(self.bias_samples) < 20:
                self.bias_samples.append(mag)
                return
            else:
                self.fz_bias = sum(self.bias_samples) / len(self.bias_samples)
                self.get_logger().info(f"Safety Monitor Biased: {self.fz_bias:.2f} N")

        # Zeroed magnitude
        current_force = abs(mag - self.fz_bias)
        
        if current_force > self.max_force:
            self.abort(f"FORCE LIMIT EXCEEDED: {current_force:.2f}N > {self.max_force}N")

    # =========================
    # Watchdog & Supervision
    # =========================
    def tick(self):
        if self.abort_triggered:
            return

        now = time.time()
        
        # Watchdog: Have we heard from the sensor?
        if (now - self.last_msg_time) > self.watchdog_timeout:
            # Only trigger after startup grace period (5s) using reliable start time
            if (now - self.node_start_time) > 5.0:
                 self.abort(f"SENSOR TIMEOUT (Watchdog): No data for {self.watchdog_timeout}s")

    def get_start_time(self):
         # DEPRECATED/UNUSED
         return 0

    def abort(self, reason: str):
        if self.abort_triggered:
            return

        self.abort_triggered = True
        msg = String()
        msg.data = f"ABORT | {reason}"
        self.pub_abort.publish(msg)
        
        # Spam it a bit to ensure receipt
        for _ in range(5):
             self.pub_abort.publish(msg)
             time.sleep(0.01)

        self.get_logger().error(f"!!! SAFETY ABORT TRIGGERED: {reason} !!!")


def main():
    rclpy.init()
    node = SafetyMonitor()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
