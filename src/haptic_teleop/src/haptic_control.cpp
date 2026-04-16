#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <std_msgs/msg/int32.hpp>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <ur_rtde/robotiq_gripper.h>
#include <thread>
#include <chrono>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <vector>

using namespace ur_rtde;

class HapticControl : public rclcpp::Node
{
public:
  HapticControl()
  : Node("haptic_control"), rtde_control("192.168.1.101"), rtde_receive("192.168.1.101"), gripper("192.168.1.101", 63352, true), //modifié true le 02/03
    velocity(0.1), acceleration(0.1), dt(1.0/125), lookahead_time(0.07), gain(500),
    button_pressed_(0), reference_position_({0.0, 0.0, 0.0}), prev_btn_(0), first_position(true),
    reference_orientation_({0.0, 0.0, 0.0}), current_position_({0.0, 0.0, 0.0}), current_orientation_({0.0, 0.0, 0.0}),
    ref_ori_robot_({0.0, 0.0, 0.0}), ref_pos_robot_({0.0, 0.0, 0.0}), gripper_closed(false)
  {
    // Souscription au topic des données haptiques
    haptic_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
      "/haptic_position", 10,
      std::bind(&HapticControl::haptic_callback, this, std::placeholders::_1));

    stylus_state_ = this->create_subscription<std_msgs::msg::Int32>(
      "/button_pressed", 10,
      std::bind(&HapticControl::stylus_state, this, std::placeholders::_1));

    //std::vector<double> init_pose = {-2.3, -1.81, -1.57, -1.27, 1.64, 0.1};
    //std::vector<double> init_pose = {-3.5, -1.5, 1.5, -1.3, -1.0, 0.0};
    std::vector<double> init_pose = {-2.7925, -0.8727, -1.57, -1.92, 1.5708, 0.0};

    rtde_control.moveJ(init_pose, velocity, acceleration);
    gripper.connect();
    gripper.activate();
    gripper.open(1.0, 0.0, RobotiqGripper::WAIT_FINISHED);

    // Ajoutée le 02/03 
    // gripper.connect();
    // RCLCPP_INFO(this->get_logger(), "Gripper connecte");

    // gripper.activate();
    // RCLCPP_INFO(this->get_logger(), "Activation envoyee au gripper");

    // gripper.open(1.0, 0.0, RobotiqGripper::WAIT_FINISHED);
    // RCLCPP_INFO(this->get_logger(), "Commande open envoyee");

  }

  ~HapticControl()
  {
    gripper.disconnect();
    rtde_control.servoStop();
    rtde_control.stopScript();
  }

private:

  bool in_workspace(const std::array<double,6>& pose)
  {
    //const double x_min = -0.4, x_max = -0.08;
    //const double y_min = -0.34, y_max = -0.17;
    const double z_min =0.012 , z_max = 0.33;
    //const double rx_min = 1.1, rx_max = 1.3;
    //const double ry_min = 2.65, ry_max = 3.1;
    //const double rz_min = -0.16, rz_max = -0.01;

    if (  pose[2] < z_min || pose[2] > z_max) {
      return false;
    }

    return true;
  }

  void stylus_state(const std_msgs::msg::Int32::SharedPtr msg)
  {
    button_pressed_ = msg->data;

    if (button_pressed_ ==0) {
      first_position = true;
    }
    
    
    else if (button_pressed_ == 2) { // grip
          if (!gripper_closed) {
            gripper.setUnit(RobotiqGripper::POSITION, RobotiqGripper::UNIT_DEVICE);
            gripper.setUnit(RobotiqGripper::SPEED, RobotiqGripper::UNIT_DEVICE);
            gripper.setUnit(RobotiqGripper::FORCE, RobotiqGripper::UNIT_DEVICE);
            gripper.move(255, 5, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            while (RobotiqGripper::MOVING == gripper.objectDetectionStatus())
            {
              std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            gripper_closed = true;
          } else {
            gripper.open(1.0, 0.0, RobotiqGripper::WAIT_FINISHED);
            gripper_closed = false;
          }
        }
    
  }

  void haptic_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
  {
    //rclcpp::Time msg_time = msg->header.stamp;
    rclcpp::Time msg_time = this->now();
    current_position_ = {msg->pose.position.x, msg->pose.position.y, msg->pose.position.z};
    tf2::Quaternion q(msg->pose.orientation.x, msg->pose.orientation.y,
                      msg->pose.orientation.z, msg->pose.orientation.w);

    tf2::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    current_orientation_ = {roll, pitch, yaw};

    
    {  
      // get robot pose 
      std::vector<double> tcp_pose = rtde_receive.getActualTCPPose();
      if (tcp_pose.size() != 6) {
        RCLCPP_ERROR(this->get_logger(), "Erreur de récupération de la pose TCP.");
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        return;
      }

      // copy data under lock
      int btn;
      std::array<double, 3> curr_pos, curr_ori;
      bool have_target = false;
       
      btn = button_pressed_;
      curr_pos = {current_position_[0], current_position_[1], current_position_[2]};
      curr_ori = {current_orientation_[0], current_orientation_[1], current_orientation_[2]};
      

      if (first_position == true && btn == 1) {
            if (current_position_[0] != 0.0 || current_position_[1] != 0.0 || current_position_[2] != 0.0) {
                reference_position_ = {curr_pos[0], curr_pos[1], curr_pos[2]};
                reference_orientation_ = {curr_ori[0], curr_ori[1], curr_ori[2]};
                ref_pos_robot_ = {tcp_pose[0], tcp_pose[1], tcp_pose[2]};
                ref_ori_robot_ = {tcp_pose[3], tcp_pose[4], tcp_pose[5]};
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            first_position = false;
            return;
            }
      }

      if (btn == 0 && prev_btn_ !=0) {
        reference_position_ = {0.0, 0.0, 0.0};
        reference_orientation_ = {0.0, 0.0, 0.0};
      }

      if (btn ==1 && prev_btn_ ==1) {
        have_target = true;
      }

      prev_btn_ = btn;

      // compute deltas and target
      std::array<double, 3> ref_pos, ref_ori;
        
      ref_pos = {reference_position_[0], reference_position_[1], reference_position_[2]};
      ref_ori = {reference_orientation_[0], reference_orientation_[1], reference_orientation_[2]};

    
      std::array<double,3> delta_position = {curr_pos[0] - ref_pos[0],
                                               curr_pos[1] - ref_pos[1],
                                               curr_pos[2] - ref_pos[2]};
                                        
      std::array<double,3> delta_orientation = {curr_ori[0] - ref_ori[0],
                                                  curr_ori[1] - ref_ori[1],
                                                  curr_ori[2] - ref_ori[2]};

      std::array<double,6> target;

      // apply button action
      if (btn == 1) { // move
          target = {delta_position[0] + ref_pos_robot_[0],
                    delta_position[1] + ref_pos_robot_[1],
                    delta_position[2] + ref_pos_robot_[2],
                    delta_orientation[0]*0.04 + ref_ori_robot_[0],
                    delta_orientation[1]*0.04 + ref_ori_robot_[1],
                    delta_orientation[2]*0.04 + ref_ori_robot_[2]};

          //RCLCPP_INFO(this->get_logger(), "delta pos: [%.2f, %.2f, %.2f]", delta_position[0], delta_position[1], delta_position[2]);

      }


      if (!have_target) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        return;
      }  
      
      // safety check
      if (!in_workspace(target)) {
        RCLCPP_WARN(this->get_logger(), "Consigne hors de l'espace de travail. Arrêt du mouvement.");
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        return;
      }

      bool kinematics_inv = rtde_control.getInverseKinematicsHasSolution({target[0], target[1], target[2], target[3], target[4], target[5]});

      if (!kinematics_inv) {
        RCLCPP_ERROR(this->get_logger(), "Erreur de cinématique inverse. Arrêt du mouvement.");
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        return;
      }

      // move robot
      auto t_start = rtde_control.initPeriod();
      rtde_control.servoL({target[0], target[1], target[2], target[3], target[4], target[5]},
                          velocity, acceleration, dt, lookahead_time, gain);
      rtde_control.waitPeriod(t_start);
    }
  }

  // Paramètres
  RTDEControlInterface rtde_control;
  RTDEReceiveInterface rtde_receive;
  RobotiqGripper gripper;
  int button_pressed_;
  bool gripper_closed;
  int prev_btn_;
  bool first_position;
  // Positions
  std::vector<double> reference_position_;
  std::vector<double> reference_orientation_;
  std::vector<double> current_position_;
  std::vector<double> current_orientation_;
  std::vector<double> ref_pos_robot_;
  std::vector<double> ref_ori_robot_;
  // Paramètres de contrôle
  double velocity, acceleration, dt, lookahead_time, gain;


  // ROS
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr haptic_sub_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr stylus_state_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<HapticControl>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
