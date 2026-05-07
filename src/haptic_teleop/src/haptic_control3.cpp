#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <std_msgs/msg/int32.hpp>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
//#include <ur_rtde/robotiq_gripper.h> //Commenté le 20/03 à 12h34 
#include <thread>
#include <chrono>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <vector>
// Ajouté le 02/03 à 22h
#include <geometry_msgs/msg/wrench_stamped.hpp>
// Commenté le 03/03 à 17h30 - plus besoin avec zeroFtSensor (remplace le bias learning)
// #include <numeric>
#include <cmath>

using namespace ur_rtde;


//Ajouté le 18/03 à 16h41
#include <signal.h>

//Ajouté le 19/03 à 12h38
#include <atomic>

//Ajouté le 31/03 à 11h10
#include <std_srvs/srv/trigger.hpp>


class HapticControl : public rclcpp::Node
{
public:
  HapticControl()
  : Node("haptic_control"), rtde_control("192.168.1.101"), rtde_receive("192.168.1.101"), //gripper("192.168.1.101", 63352, true), //Modifié "true" le 04/03 à 12h13 // Commenté le 20/03 à 12h30
    velocity(0.1), acceleration(0.1), dt(1.0/125), lookahead_time(0.15), gain(500), //Modifié lookahead_time(0.07) à 0.15 le 26/03 à 15h34  //Modifié dt(1.0/125) à dt(1.0/54) le 25/03 à 17h42
    button_pressed_(0), reference_position_({0.0, 0.0, 0.0}), prev_btn_(0), first_position(true),
    reference_orientation_({0.0, 0.0, 0.0}), current_position_({0.0, 0.0, 0.0}), current_orientation_({0.0, 0.0, 0.0}),
    ref_ori_robot_({0.0, 0.0, 0.0}), ref_pos_robot_({0.0, 0.0, 0.0}), //gripper_closed(false), //Commenté le 20/03 à 12h36
    // Ajouté le 03/03 à 14h00 - initialisation filtre passe-bas position
    filtered_position_({0.0, 0.0, 0.0}), filter_initialized_(false)
    // Commenté le 03/03 à 17h30 - bias learning remplacé par zeroFtSensor
    // bias_ready_(false), bias_collecting_(true), force_bias_({0.0, 0.0, 0.0})
  {
    RCLCPP_INFO(this->get_logger(), "Constructeur demarre"); // Ajouté le 04/03

    haptic_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
      "/haptic_position", 10,
      std::bind(&HapticControl::haptic_callback, this, std::placeholders::_1));

    stylus_state_ = this->create_subscription<std_msgs::msg::Int32>(
      "/button_pressed", 10,
      std::bind(&HapticControl::stylus_state, this, std::placeholders::_1));

    // Ajouté le 02/03 à 22h
    force_sub_ = this->create_subscription<geometry_msgs::msg::WrenchStamped>(
      "/force_torque_sensor_broadcaster/wrench", 10,
      std::bind(&HapticControl::force_callback, this, std::placeholders::_1));

    // Ajouté le 02/03 à 22h
    haptic_force_pub_ = this->create_publisher<geometry_msgs::msg::WrenchStamped>("/haptic_force", 10);

    //std::vector<double> init_pose = {-2.3, -1.81, -1.57, -1.27, 1.64, 0.1};
    //std::vector<double> init_pose = {-3.5, -1.5, 1.5, -1.3, -1.0, 0.0};
    //std::vector<double> init_pose = {-2.7925, -0.8727, -1.57, -1.92, 1.5708, 0.0};

    //Commenté le 16/03 à 14h25 
    //std::vector<double> init_pose = {-2.79, -1.27, -1.42, -2.01, 1.56, 6.22};

    //Ajouté le 16/03 à 14h26
    //std::vector<double> init_pose = {-3.14, -1.27, -1.42, -2.01, 1.56, 6.22};

    //Ajouté le 24/04 à 12h30 
    auto deg2rad = [](double d){ return d * M_PI / 180.0; };
    std::vector<double> init_pose = {
        deg2rad(-15.0),    // J1 Base
        deg2rad(-113.1),   // J2 Shoulder
        deg2rad(93.6),     // J3 Elbow
        deg2rad(-70.5),    // J4 Wrist1
        deg2rad(-90.0),    // J5 Wrist2
        deg2rad(180.0)     // J6 Wrist3
    };

    // moveJ est bloquant : robot garanti immobile avant le tare
    
    //Ajouté logs debug le 04/03 à 12h34
    RCLCPP_INFO(this->get_logger(), "Debut moveJ...");
    rtde_control.moveJ(init_pose, velocity, acceleration);
    RCLCPP_INFO(this->get_logger(), "moveJ termine.");

    //Commenté le 20/03 à 12h32
    //RCLCPP_INFO(this->get_logger(), "moveJ termine. Connexion gripper...");
    //gripper.connect();
    //RCLCPP_INFO(this->get_logger(), "Gripper connecte. Activation...");
    //gripper.activate();
    //RCLCPP_INFO(this->get_logger(), "Gripper active. Open...");
    //gripper.open(1.0, 0.0, RobotiqGripper::WAIT_FINISHED);

    RCLCPP_INFO(this->get_logger(), "Initialisation complete.");


    // Commenté le 03/03 à 17h30 - délai remplacé par zeroFtSensor
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // Ajouté le 03/03 à 17h30 - tare hardware du capteur ATI via RTDE
    // Remplace tout le bias learning : plus propre, plus fiable, une seule ligne
    rtde_control.zeroFtSensor();
    RCLCPP_INFO(this->get_logger(), "Tare capteur ATI effectuee - Retour de force actif.");

    //Ajouté le 31/03 à 11h10 
    tare_service_ = this->create_service<std_srvs::srv::Trigger>(
      "/tare_sensor",
      [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>,
            std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
          rtde_control.zeroFtSensor();
          response->success = true;
          response->message = "Tare effectuee";
      });

    // Ajoutée le 02/03
    // gripper.connect();
    // gripper.activate();
    // gripper.open(1.0, 0.0, RobotiqGripper::WAIT_FINISHED);

    // Commenté le 03/03 à 17h30 - remplacé par le log zeroFtSensor ci-dessus
    // RCLCPP_INFO(this->get_logger(), "Robot en position initiale. Debut de la collecte du biais en repere base...");
  }

  ~HapticControl()
  {
    //gripper.disconnect(); //Commenté le 20/03 à 12h32
    rtde_control.servoStop();
    rtde_control.stopScript();
  }

private:

  bool in_workspace(const std::array<double,6>& pose)
  {
    // Commenté le 03/03 à 14h00 - limites X et Y trop restrictives, à recalibrer
    // Commenté le 16/03 à 17h45

    // const double x_min = -0.55, x_max = 0.10;
    // const double y_min = -0.50, y_max = 0.20;
    // const double z_min = 0.012, z_max = 0.33;

    const double x_min = -0.38, x_max = 0.10;
    const double y_min = -0.35, y_max = 0.35;
    const double z_min = -0.02, z_max = 0.38; // Modifié z_min = 0.012 en 0.085 le 19/03 à 11h56 // Modifié z_min = 0.012 en -0.02 le 24/03 à 16h16

    // if (pose[2] < z_min || pose[2] > z_max) {
    //   return false;
    // }

    //Ajouté le 16/03 à 17h39    
    if (pose[0] < x_min || pose[0] > x_max) return false;
    if (pose[1] < y_min || pose[1] > y_max) return false;
    if (pose[2] < z_min || pose[2] > z_max) return false;

    return true;
  }

  void stylus_state(const std_msgs::msg::Int32::SharedPtr msg)
  {
    button_pressed_ = msg->data;

    if (button_pressed_ == 0) {
      first_position = true;
      // Ajouté le 03/03 à 14h00 - réinitialiser le filtre quand on relâche le bouton
      filter_initialized_ = false;
    }

    //Commenté le 20/03 à 12h36

    // else if (button_pressed_ == 2) { // grip
    //   if (!gripper_closed) {
    //     gripper.setUnit(RobotiqGripper::POSITION, RobotiqGripper::UNIT_DEVICE);
    //     gripper.setUnit(RobotiqGripper::SPEED, RobotiqGripper::UNIT_DEVICE);
    //     gripper.setUnit(RobotiqGripper::FORCE, RobotiqGripper::UNIT_DEVICE);
    //     gripper.move(255, 5, 0);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //     while (RobotiqGripper::MOVING == gripper.objectDetectionStatus())
    //     {
    //       std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //     }
    //     gripper_closed = true;
    //   } else {
    //     gripper.open(1.0, 0.0, RobotiqGripper::WAIT_FINISHED);
    //     gripper_closed = false;
    //   }
    // }
  }

  void haptic_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
  {
    rclcpp::Time msg_time = this->now();

    // Ajouté le 03/03 à 14h00 - filtre passe-bas sur la position du haptic
    // Formule : position_filtrée = alpha × position_précédente + (1-alpha) × position_actuelle
    // Plus alpha est grand → robot plus lisse mais plus en retard
    // Plus alpha est petit → robot plus réactif mais plus saccadé

    const double alpha = 0.85; // Modifié "0.7" le 03/03 à 14h30 //Commenté le 19/03 à 13h08

    //const double alpha = (current_force_magnitude_ > 15.0) ? 0.92 : 0.85; //Ajouté le 19/03 à 13h08 (test pour changer alpha selon zone)

    double raw_x = msg->pose.position.x;
    double raw_y = msg->pose.position.y;
    double raw_z = msg->pose.position.z;

    // Ajouté le 03/03 à 14h00 - initialiser le filtre avec la première position reçue
    if (!filter_initialized_) {
      filtered_position_ = {raw_x, raw_y, raw_z};
      filter_initialized_ = true;
    } else {
      filtered_position_[0] = alpha * filtered_position_[0] + (1.0 - alpha) * raw_x;
      filtered_position_[1] = alpha * filtered_position_[1] + (1.0 - alpha) * raw_y;
      filtered_position_[2] = alpha * filtered_position_[2] + (1.0 - alpha) * raw_z;
    }

    // Ajouté le 03/03 à 14h00 - utiliser la position filtrée au lieu de la position brute
    current_position_ = {filtered_position_[0], filtered_position_[1], filtered_position_[2]};

    tf2::Quaternion q(msg->pose.orientation.x, msg->pose.orientation.y,
                      msg->pose.orientation.z, msg->pose.orientation.w);

    tf2::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    current_orientation_ = {roll, pitch, yaw};

    {
      std::vector<double> tcp_pose = rtde_receive.getActualTCPPose(); //Récupéper pose TCP dans le repère BASE
      
      if (tcp_pose.size() != 6) {
        RCLCPP_ERROR(this->get_logger(), "Erreur de récupération de la pose TCP.");
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        return;
      }

      //RCLCPP_INFO(this->get_logger(), "TCP robot - x:%.3f y:%.3f z:%.3f", tcp_pose[0], tcp_pose[1], tcp_pose[2]); //Ajouté le 13/03 à 13h41

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

      if (btn == 0 && prev_btn_ != 0) {
        reference_position_ = {0.0, 0.0, 0.0};
        reference_orientation_ = {0.0, 0.0, 0.0};
      }

      if (btn == 1 && prev_btn_ == 1) {
        have_target = true;
      }

      prev_btn_ = btn;

      std::array<double, 3> ref_pos, ref_ori;
      ref_pos = {reference_position_[0], reference_position_[1], reference_position_[2]};
      ref_ori = {reference_orientation_[0], reference_orientation_[1], reference_orientation_[2]};

      std::array<double,3> delta_position = {curr_pos[0] - ref_pos[0],
                                              curr_pos[1] - ref_pos[1],
                                              curr_pos[2] - ref_pos[2]};

      std::array<double,3> delta_orientation = {curr_ori[0] - ref_ori[0],
                                                 curr_ori[1] - ref_ori[1],
                                                 curr_ori[2] - ref_ori[2]};

      //Ajouté le 13/03 à 18h21                                    
      //RCLCPP_INFO(this->get_logger(), "Delta - x:%.3f y:%.3f z:%.3f", delta_position[0], delta_position[1], delta_position[2]);

      //Ajouté le 16/03 à 14h04     
      RCLCPP_INFO(this->get_logger(), "Delta x:%.3f y:%.3f z:%.3f | Robot x:%.3f y:%.3f z:%.3f",
      delta_position[0], delta_position[1], delta_position[2],
      tcp_pose[0], tcp_pose[1], tcp_pose[2]);

      std::array<double,6> target;

      if (btn == 1) {
        // Ajouté le 03/03 à 14h00 - scaling du workspace
        // 1cm de main = 1.5cm de robot. À ajuster : 1.0 (précis) à 3.0 (rapide)
        const double scaling_factor = 1.0; // Modifié "3.0" le 03/03 à 14h30 // Commenté le 19/03 à 12h38

        //const double scaling_factor = (current_force_magnitude_ > 15.0) ? 1.0 : 1.5; //Ajouté le 19/03 à 12h38

        //Ajouté le 19/03 à 17h12
        //double force_mag = current_force_magnitude_.load();
        //double t = std::min(force_mag / 30.0, 1.0);
        //const double scaling_factor = 1.5 - 0.5 * t;

        target = {delta_position[0] * scaling_factor + ref_pos_robot_[0],
                  delta_position[1] * scaling_factor + ref_pos_robot_[1],
                  delta_position[2] * scaling_factor + ref_pos_robot_[2],
                  /*delta_orientation[0]*0.04 + */ ref_ori_robot_[0],  //Commenté le 20/03 à 13h23
                  /*delta_orientation[1]*0.04 + */ ref_ori_robot_[1],
                  /*delta_orientation[2]*0.04 + */ ref_ori_robot_[2]};
      }

      if (!have_target) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        return;
      }

      if (!in_workspace(target)) {
        RCLCPP_WARN(this->get_logger(), "Consigne hors de l'espace de travail. Arrêt du mouvement.");
        //std::this_thread::sleep_for(std::chrono::milliseconds(2));
        rtde_control.servoStop(); //Ajouté le 17/03 à 15h09
        return;
      }

      bool kinematics_inv = rtde_control.getInverseKinematicsHasSolution({target[0], target[1], target[2], target[3], target[4], target[5]});

      if (!kinematics_inv) {
        RCLCPP_ERROR(this->get_logger(), "Erreur de cinématique inverse. Arrêt du mouvement.");
        //std::this_thread::sleep_for(std::chrono::milliseconds(2));
        rtde_control.servoStop(); //Ajouté le 17/03 à 15h09
        return;
      }


      //double current_lookahead = (current_force_magnitude_ > 15.0) ? 0.15 : 0.07; // Ajouté le 19/03 à 13h18
      //double current_gain = (current_force_magnitude_ > 15.0) ? 200 : 500; //Ajouté le 19/03 à 17h01
      auto t_start = rtde_control.initPeriod();
      rtde_control.servoL({target[0], target[1], target[2], target[3], target[4], target[5]},
                          velocity, acceleration, dt, lookahead_time, gain);
      rtde_control.waitPeriod(t_start);
    }
  }

  // Ajouté le 02/03 à 22h
  void force_callback(const geometry_msgs::msg::WrenchStamped::SharedPtr msg)
  {
    // ETAPE 1 : Récupérer l'orientation actuelle du robot
    std::vector<double> tcp_pose = rtde_receive.getActualTCPPose();
    if (tcp_pose.size() != 6) return;

    // ETAPE 2 : Conversion axis-angle → quaternion
    // Commenté le 03/03 à 10h - setRPY incorrect : getActualTCPPose() retourne
    // l'orientation en vecteur de rotation (axis-angle), pas en RPY
    // tf2::Quaternion q;
    // q.setRPY(tcp_pose[3], tcp_pose[4], tcp_pose[5]);

    // Ajouté le 03/03 à 10h - conversion correcte axis-angle → quaternion
    tf2::Vector3 rot_vec(tcp_pose[3], tcp_pose[4], tcp_pose[5]);
    double angle = rot_vec.length();
    tf2::Quaternion q;
    if (angle > 1e-10) {
      tf2::Vector3 axis = rot_vec.normalized();
      q.setRotation(axis, angle);
    } else {
      q = tf2::Quaternion(0, 0, 0, 1);
    }

    // ETAPE 3 : Transformer la force de tool0 → repère base
    tf2::Vector3 force_tool(
      msg->wrench.force.x,
      msg->wrench.force.y,
      msg->wrench.force.z
    );
    tf2::Vector3 force_base = tf2::quatRotate(q, force_tool);

    // Commenté le 03/03 à 17h30 - soustraction biais supprimée, remplacée par zeroFtSensor()
    // Le capteur est taré hardware au démarrage, plus besoin de soustraire un biais ici.
    // tf2::Vector3 force_base(
    //   force_base_raw.x() - force_bias_[0],
    //   force_base_raw.y() - force_bias_[1],
    //   force_base_raw.z() - force_bias_[2]
    // );

    // ETAPE 4 : Publier la force transformée sur /haptic_force
    geometry_msgs::msg::WrenchStamped out_msg;
    out_msg.header.stamp = this->now();
    out_msg.header.frame_id = "base";
    out_msg.wrench.force.x = force_base.x();
    out_msg.wrench.force.y = force_base.y();
    out_msg.wrench.force.z = force_base.z();

    //Ajouté le 19/03 à 12h37
    current_force_magnitude_ = std::sqrt(
      force_base.x()*force_base.x() + 
      force_base.y()*force_base.y() + 
      force_base.z()*force_base.z()
  );


    haptic_force_pub_->publish(out_msg);
  }

  // Paramètres
  RTDEControlInterface rtde_control;
  RTDEReceiveInterface rtde_receive;
  //RobotiqGripper gripper; //Commenté le 20/03 à 12h34
  int button_pressed_;
  //bool gripper_closed; //Commenté le 20/03 à 12h34
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
  // Ajouté le 02/03 à 22h
  rclcpp::Subscription<geometry_msgs::msg::WrenchStamped>::SharedPtr force_sub_;
  // Ajouté le 02/03 à 22h
  rclcpp::Publisher<geometry_msgs::msg::WrenchStamped>::SharedPtr haptic_force_pub_;

  // Ajouté le 03/03 à 14h00 - variables pour le filtre passe-bas sur la position haptic
  std::vector<double> filtered_position_;
  bool filter_initialized_;

  //Ajouté le 19/03 à 12h36
  std::atomic<double> current_force_magnitude_{0.0};

  //Ajouté le 31/03 à 11h10
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr tare_service_;

  // Commenté le 03/03 à 17h30 - variables bias learning supprimées, remplacées par zeroFtSensor
  // std::vector<double> bias_buf_x_;
  // std::vector<double> bias_buf_y_;
  // std::vector<double> bias_buf_z_;
  // bool bias_ready_;
  // bool bias_collecting_;
  // std::array<double, 3> force_bias_;
};

// int main(int argc, char *argv[])
// {
//   rclcpp::init(argc, argv);
//   auto node = std::make_shared<HapticControl>();
//   rclcpp::spin(node);
//   rclcpp::shutdown();
//   return 0;
// }


//Ajouté le 18/03 à 16h43
std::shared_ptr<HapticControl> g_node = nullptr;

void signal_handler(int signum)
{
  RCLCPP_INFO(rclcpp::get_logger("haptic_control"), "Signal recu (%d), deconnexion propre...", signum);
  if (g_node) g_node.reset();
  rclcpp::shutdown();
}

//Ajouté le 18/03 à 16h43
int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGABRT, signal_handler);
  signal(SIGSEGV, signal_handler);

  while (rclcpp::ok()) {
    try {
      g_node = std::make_shared<HapticControl>();
      rclcpp::spin(g_node);
      break;
    } catch (const std::exception& e) {
      RCLCPP_WARN(rclcpp::get_logger("main"), "Echec: %s — nouvelle tentative dans 3s...", e.what());
      if (g_node) g_node.reset();
      for (int i = 3; i > 0 && rclcpp::ok(); i--) {
        RCLCPP_INFO(rclcpp::get_logger("main"), "Relance dans %ds...", i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
    }
  }

  rclcpp::shutdown();
  return 0;
}