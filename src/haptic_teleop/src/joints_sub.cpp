#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <vector>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <std_msgs/msg/bool.hpp>

using namespace ur_rtde;

class JointsSubscriber : public rclcpp::Node
{
public:
    JointsSubscriber()
    : Node("joints_subscriber"), position_({-2.3, -1.81, -1.57, -1.27, 1.64, 0.1}),
      rtde_control("192.168.56.101"), rtde_receive("192.168.56.101"),
      velocity(0.1), acceleration(0.1), dt(1.0/125), lookahead_time(0.1), gain(200), init(false)
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "joint_states_pub", 10, std::bind(&JointsSubscriber::joints_callback, this, std::placeholders::_1));

        rtde_control.moveJ(position_, velocity, acceleration);
        
    }

    ~JointsSubscriber()
    {
        // Save errors to CSV file
        std::ofstream out("joint_errors.csv");
        if (out.is_open()) {
            out << "time,joint_1,joint_2,joint_3,joint_4,joint_5,joint_6\n";
            for (size_t i = 0; i < pose_errors_.size(); ++i) {
                out << i * (1.0/125) << ",";
                for (size_t j = 0; j < 6; ++j) {
                    out << pose_errors_[i][j];
                    if (j < 5) out << ",";
                }
                out << "\n";
            }
            out.close();
        }
        std::ofstream out2("total_joint_errors.csv");
        if (out2.is_open()) {
            out2 << "time,total_error\n";
            for (size_t i = 0; i < total_errors_.size(); ++i) {
                out2 << i * (1.0/125) << "," << total_errors_[i] << "\n";
            }
            out2.close();
        }
        
        rtde_control.stopScript();
        rtde_control.servoStop();
        }

private:
    void joints_callback(const sensor_msgs::msg::JointState::SharedPtr msg)
    {
        if (msg->position.size() != 6) return;
        /*
        if (!init){
            rtde_control.moveJ(position_, velocity, acceleration);
            init = true;
            return;
        }
        */

        for (size_t i = 0; i < 6; ++i)
            position_[i] = msg->position[i];
        position_[0] -= 1.57;

        auto t_start = rtde_control.initPeriod();
        rtde_control.servoJ(position_, velocity, acceleration, dt, lookahead_time, gain);
        rtde_control.waitPeriod(t_start);

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        std::vector<double> current_joints = rtde_receive.getActualQ();

        if (current_joints.size() != 6) return;
        std::array<double, 6> errors;
        for (size_t i = 0; i < 6; ++i)
            errors[i] = current_joints[i] - position_[i];
        
        pose_errors_.push_back(errors);
        if (pose_errors_.size() > 1000) {
            pose_errors_.erase(pose_errors_.begin());
        }

        double total_error = 0.0;
        for (double e : errors) {
            total_error += std::abs(e);
        }
        total_errors_.push_back(total_error);
        if (total_errors_.size() > 1000) {
            total_errors_.erase(total_errors_.begin());
        }
    
    }

    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;
    std::vector<double> position_; // Position des articulations
    RTDEControlInterface rtde_control;
    RTDEReceiveInterface rtde_receive;
    double velocity, acceleration, dt, lookahead_time, gain;
    std::vector<std::array<double, 6>> pose_errors_;
    std::vector<double> total_errors_;
    bool init;

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JointsSubscriber>());
    rclcpp::shutdown();
    return 0;
}