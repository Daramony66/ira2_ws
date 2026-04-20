#include "rclcpp/rclcpp.hpp"
#include "haptic_teleop/srv/SystemStateService.hpp"

using namespace std::chrono_literals;

class SystemStateServiceNode : public rclcpp::Node
{
public :
    SystemStateServiceNode() : Node("system_state")
    {
        state_client = this->create_client<haptic_teleop::srv::SystemStateService>("system_state_srv");

        while (!state_client->wait_for_service(1s))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for Unity service...");
        }
    }

    void change_state(int mode_id) {
        auto request = std::make_shared<haptic_teleop::srv::SystemStateService::Request>();
        request->command = mode_id;

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

private :
    rclcpp::Client<haptic_teleop::srv::SystemStateService>::SharedPtr state_client;
};