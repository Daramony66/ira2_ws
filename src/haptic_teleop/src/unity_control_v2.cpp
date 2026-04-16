#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <std_msgs/msg/bool.hpp>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

using namespace ur_rtde;

class UnityControl : public rclcpp::Node {
public:
    UnityControl()
     : Node("unity_control"), rtde_control("192.168.56.101"), rtde_receive("192.168.56.101"), in_workspace_(true) {

    unity_position_subscriber_ = this->create_subscription<geometry_msgs::msg::Pose>(
      "/unity_position", 10, std::bind(&UnityControl::pose_unity_callback, this, std::placeholders::_1));

    robot_in_workspace_publisher_ = this->create_publisher<std_msgs::msg::Bool>(
      "/robot_in_workspace", 10);

    std::vector<double> init_pose = {-2.3, -1.81, -1.57, -1.27, 1.64, 0.1};
    rtde_control.moveJ(init_pose, 0.1, 0.1);
  
  }

  ~UnityControl() {
    rtde_control.stopScript();
    rtde_control.servoStop();
  }

private:

  void pose_unity_callback(const geometry_msgs::msg::Pose::SharedPtr msg) {

    float new_x = msg->position.x;
    float new_y = msg->position.y;
    float new_z = msg->position.z;

    std::vector<double> tcp_pose = rtde_receive.getActualTCPPose();
    if (tcp_pose.size() != 6) {
        RCLCPP_ERROR(this->get_logger(), "Erreur de récupération de la pose TCP.");
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        return;
      }
    
    // Check if the new position admits an inverse kinematics solution
    bool kinematics_inv = rtde_control.getInverseKinematicsHasSolution({new_x, new_y, new_z, tcp_pose[3], tcp_pose[4], tcp_pose[5]});

    if (!kinematics_inv || new_z < 0.012) {
        RCLCPP_ERROR(this->get_logger(), "Position en dehors de l'espace de travail.");
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        in_workspace_ = false;
        std_msgs::msg::Bool msg;
        msg.data = in_workspace_;
        robot_in_workspace_publisher_->publish(msg);
        return;
      } else {
        in_workspace_ = true;
        std_msgs::msg::Bool msg;
        msg.data = in_workspace_;
        robot_in_workspace_publisher_->publish(msg);
      }
    
    auto t_start = rtde_control.initPeriod();
    rtde_control.servoL({new_x, new_y, new_z, tcp_pose[3], tcp_pose[4], tcp_pose[5]},
                        0.1, 0.1, 0.008, 0.1, 200);
    rtde_control.waitPeriod(t_start);
 
  }

  rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr unity_position_subscriber_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr robot_in_workspace_publisher_;
  RTDEControlInterface rtde_control;
  RTDEReceiveInterface rtde_receive;
  bool in_workspace_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<UnityControl>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}