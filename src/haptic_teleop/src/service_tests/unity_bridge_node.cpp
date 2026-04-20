#include "rclcpp/rclcpp.hpp"
#include "haptic_teleop/srv/AppControlService.hpp"
#include "haptic_teleop/srv/ContactPointService.hpp"
#include "haptic_teleop/srv/SystemStateService.hpp"

using namespace std::chrono_literals;
using Point = geometry_msgs::msg::Point;

class UnityBridgeNode : public rclcpp::Node
{
public :
    Point cp; // contact point

    UnityBridgeNode() : Node("unity_bridge")
    {
        app_control_client = this->create_client<haptic_teleop::srv::AppControlService>("app_control");
        contact_point_client = this->create_client<haptic_teleop::srv::ContactPointService>("cp_position");
        state_client = this->create_client<haptic_teleop::srv::SystemStateService>("system_state");

        // Attendre que tous les services soient disponibles
        while (!app_control_client->wait_for_service(1s) || 
               !contact_point_client->wait_for_service(1s) || 
               !state_client->wait_for_service(1s))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for Unity services...");
        }
    }

    void change_state(int state_id) {
        // state_id =
        // 0 : pre-calibration
        // 1 : calibration
        // 2 : punch
        // 3 : push by hand
        // 4 : push by finger


        auto request = std::make_shared<haptic_teleop::srv::SystemStateService::Request>();
        request->command = state_id;

        state_client->async_send_request(
            request,
            [this](rclcpp::Client<haptic_teleop::srv::SystemStateService>::SharedFuture future)
            {
                auto response = future.get();

                if (response->success)
                {
                    // successfully changed state, tu peux faire qqch ici
                }
                else
                {
                    // error handling, tu peux faire qqch ici aussi
                }
            }
        );
    }

    void change_mode(int mode_id) {
        // mode_id =
        // 0 : play
        // 1 : stop
        // 2 : reset


        auto request = std::make_shared<haptic_teleop::srv::AppControlService::Request>();
        request->command = mode_id;

        app_control_client->async_send_request(
            request,
            [this](rclcpp::Client<haptic_teleop::srv::AppControlService>::SharedFuture future)
            {
                auto response = future.get();

                if (response->success)
                {
                    // successfully changed mode, tu peux faire qqch ici
                }
                else
                {
                    // error handling, tu peux faire qqch ici aussi
                }
            }
        );
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
    rclcpp::Client<haptic_teleop::srv::AppControlService>::SharedPtr app_control_client;
    rclcpp::Client<haptic_teleop::srv::ContactPointService>::SharedPtr contact_point_client;
    rclcpp::Client<haptic_teleop::srv::SystemStateService>::SharedPtr state_client;
};