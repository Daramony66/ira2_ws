#include "rclcpp/rclcpp.hpp"
#include "haptic_teleop/srv/AppControlService.hpp"

using namespace std::chrono_literals;

class AppControlServiceNode : public rclcpp::Node
{
public :
    AppControlServiceNode() : Node("app_control")
    {
        app_control_client = this->create_client<haptic_teleop::srv::AppControlService>("app_control_srv");

        while (!app_control_client->wait_for_service(1s))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for Unity service...");
        }
    }

    void change_mode(int mode_id) {
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

private :
    rclcpp::Client<haptic_teleop::srv::AppControlService>::SharedPtr app_control_client;
};