#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/wrench_stamped.hpp>
#include <ur_rtde/rtde_receive_interface.h>
#include <thread>
#include <chrono>

using namespace ur_rtde;

class GetForce : public rclcpp::Node
{
public:
  GetForce()
  : Node("get_force"), rtde_receive("192.168.56.101")
  {
    force_tcp_pub = this->create_publisher<geometry_msgs::msg::WrenchStamped>("/tcp_force", 10);

    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(8),
      std::bind(&GetForce::get_force, this));
  }

private:
  void get_force()
  {
    std::vector<double> tcp_force = rtde_receive.getActualTCPForce();

    if (tcp_force.size() != 6) {
      RCLCPP_ERROR(this->get_logger(), "Erreur de récupération de la force TCP.");
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
      return;
    }

    //RCLCPP_INFO(this->get_logger(), "Force TCP: [%.2f, %.2f, %.2f, %.2f, %.2f, %.2f]",
                  //tcp_force[0], tcp_force[1], tcp_force[2],
                  //tcp_force[3], tcp_force[4], tcp_force[5]);

    // publish force
    geometry_msgs::msg::WrenchStamped force_msg;
    force_msg.header.stamp = this->now();
    force_msg.header.frame_id = "base_link";
    force_msg.wrench.force.x = tcp_force[0];
    force_msg.wrench.force.y = tcp_force[1];
    force_msg.wrench.force.z = tcp_force[2];
    force_msg.wrench.torque.x = tcp_force[3];
    force_msg.wrench.torque.y = tcp_force[4];
    force_msg.wrench.torque.z = tcp_force[5];
    force_tcp_pub->publish(force_msg);
  }

  rclcpp::Publisher<geometry_msgs::msg::WrenchStamped>::SharedPtr force_tcp_pub;
  rclcpp::TimerBase::SharedPtr timer_;
  RTDEReceiveInterface rtde_receive;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GetForce>());
  rclcpp::shutdown();
  return 0;
}