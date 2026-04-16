#include <random>
#include "haptic_teleop/srv/position_service.hpp"
#include <memory>
#include "rclcpp/rclcpp.hpp"

using namespace std::placeholders;

class PositionServiceNode : public rclcpp::Node
{
public:
    PositionServiceNode() : Node("position_service")
    {
        service_ = this->create_service<haptic_teleop::srv::PositionService>(
            "pos_srv",
            std::bind(&PositionServiceNode::new_position_callback, this, _1, _2)
        );
    }

private:
    void new_position_callback(
        const std::shared_ptr<haptic_teleop::srv::PositionService::Request> /*request*/,
        std::shared_ptr<haptic_teleop::srv::PositionService::Response> response)
    {
        // Example: generate random position
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-4.0, 4.0);

        response->output.pos_x = dis(gen);
        response->output.pos_z = dis(gen);
    }

    rclcpp::Service<haptic_teleop::srv::PositionService>::SharedPtr service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PositionServiceNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}