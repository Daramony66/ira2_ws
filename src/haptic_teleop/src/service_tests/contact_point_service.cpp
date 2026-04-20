#include "rclcpp/rclcpp.hpp"
#include "haptic_teleop/srv/ContactPointService.hpp"

using namespace std::chrono_literals;
using Point = geometry_msgs::msg::Point;

class ContactPointServiceNode : public rclcpp::Node
{
public :
    Point cp; // contact point

    ContactPointServiceNode() : Node("contact_point")
    {
        contact_point_client = this->create_client<haptic_teleop::srv::ContactPointService>("cp_position");

        while (!contact_point_client->wait_for_service(1s))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for Unity service...");
        }
    }

    void request_contact_point()
    {
        auto request =std::make_shared<haptic_teleop::srv::ContactPointService::Request>();

        request->command = 0;

        contact_point_client->async_send_request(
            request,
            [this](rclcpp::Client<haptic_teleop::srv::ContactPointService>::SharedFuture future)
            {
                auto response = future.get();

                if (!response->success) return;

                cp = response->position;
            }
        );
    }

private :
    rclcpp::Client<haptic_teleop::srv::ContactPointService>::SharedPtr contact_point_client;
};