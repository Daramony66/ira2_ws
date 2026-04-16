#include <chrono>
#include <memory>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "haptic_teleop/msg/unity_color.hpp"

using namespace std::chrono_literals;

class ColorPublisher : public rclcpp::Node
{
public:
    ColorPublisher()
    : Node("color_publisher"), count_(0)
    {
        publisher_ = this->create_publisher<haptic_teleop::msg::UnityColor>("color", 10);
        
        publish_color(); 
  
        timer_ = this->create_wall_timer(500ms, [this]() {
            rclcpp::shutdown();
        });
    }
    
private:
    void publish_color()
    {
        auto color = haptic_teleop::msg::UnityColor();
        // Generate random values between 0 and 255
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 255);
        
        color.r = dist(gen);
        color.g = dist(gen);
        color.b = dist(gen);
        color.a = 1;
        
        RCLCPP_INFO(this->get_logger(), "Publishing: r=%d, g=%d, b=%d, a=%d", 
                    color.r, color.g, color.b, color.a);
        
        this->publisher_->publish(color);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<haptic_teleop::msg::UnityColor>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ColorPublisher>());
    return 0;
}
