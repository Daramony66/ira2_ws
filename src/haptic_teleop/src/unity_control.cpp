#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>


class UnityControl : public rclcpp::Node {
public:
    UnityControl() : Node("unity_control"), pos_x_(0.0), pos_y_(0.0), pos_z_(0.0), rot_z_(0.0), last_x_(0.0), last_z_(0.0), init_(false) {
    
    effector_position_subscriber_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
      "/tcp_pose_broadcaster/pose", 10, std::bind(&UnityControl::pose_effector_callback, this, std::placeholders::_1));

    cube_position_subscriber_ = this->create_subscription<geometry_msgs::msg::Point>(
      "/cube_position", 10, std::bind(&UnityControl::pose_cube_callback, this, std::placeholders::_1));

    // client pour envoyer des scripts URScript
    urscript_client_ = this->create_publisher<std_msgs::msg::String>(
      "/urscript_interface/script_command", 10);
  }

private:

  void pose_effector_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
    // MAJ de la position initiale du robot
    if (!init_) {

      tf2::Quaternion q(
        msg->pose.orientation.x,
        msg->pose.orientation.y,
        msg->pose.orientation.z,
        msg->pose.orientation.w);
      double angle = q.getAngle();
      tf2::Vector3 axis = q.getAxis();

      pos_x_ = msg->pose.position.x;
      pos_y_ = msg->pose.position.y;
      pos_z_ = msg->pose.position.z;
      rot_x_ = axis.x() * angle;
      rot_y_ = axis.y() * angle; 
      rot_z_ = axis.z() * angle;
      init_ = true;
    }
  }
  void pose_cube_callback(const geometry_msgs::msg::Point::SharedPtr msg) {
    if (!init_) {
      return;
    }
    float new_x = msg->x + pos_x_;
    float new_z = msg->z + pos_z_;

    if (std::abs(new_x - last_x_) > 0.001 || std::abs(new_z - last_z_) > 0.001) {
      // génère une commande URScript
      
      std::string script = "movel(p[" +
        std::to_string(new_x) + "," +
        std::to_string(pos_y_) + "," +
        std::to_string(new_z) + "," +
        std::to_string(rot_x_) + "," +
        std::to_string(rot_y_) + "," +
        std::to_string(rot_z_) + "], a=0.1, v=0.1)";

      // publie le script URScript
      auto msg = std_msgs::msg::String();
      msg.data = script;
      urscript_client_->publish(msg);
      //RCLCPP_INFO(this->get_logger(), "Envoyé URScript: %s", script.c_str());

      // MAJ des positions
      last_x_ = new_x;
      last_z_ = new_z;
    }
  }

  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr effector_position_subscriber_;
  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr cube_position_subscriber_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr urscript_client_;
  float pos_x_, pos_y_, pos_z_;
  float rot_x_, rot_y_, rot_z_;
  float last_x_, last_z_;
  bool init_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<UnityControl>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}