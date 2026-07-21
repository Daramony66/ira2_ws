// haptic_control_dual.cpp
// Téléopération bilatérale à DEUX bras haptiques (expert / apprenant) sur UR3e.
// Basé sur haptic_control3.cpp (mono-bras), restructuré pour le scénario expert/apprenant.
//
// Principe :
//  - Chaque bras publie sa position sur /expert/haptic_position et /learner/haptic_position
//    et l'état de son bouton sur /expert/button_pressed et /learner/button_pressed.
//  - La cible robot est un MELANGE (blend) des deux gestes :
//        target = ref_robot + a*delta_expert + (1-a)*delta_learner
//    avec 'a' (alpha) le curseur du blend.
//  - GATING : le robot bouge si AU MOINS un bras tient le bouton.
//        les deux tiennent -> a = alpha_nominal (0.8 par defaut)
//        expert seul       -> a = 1.0
//        apprenant seul    -> a = 0.0
//        personne          -> robot immobile (servoStop)
//  - RE-ANCRAGE : a chaque changement de gating (un bras rejoint ou quitte),
//    on remet ref_robot sur le TCP actuel et les refs main des bras actifs sur
//    leur position actuelle -> la cible reste continue, AUCUN saut.
//
//  - Le retour de force du robot est transforme tool0 -> base et publie sur
//    /expert/haptic_force ET /learner/haptic_force (les deux bras sentent le robot).
//    Le couplage expert->apprenant est gere cote Unity.
//
//  - alpha_nominal est reglable a chaud via le topic /alpha (std_msgs/Float64),
//    pour tester sans recompiler.

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/wrench_stamped.hpp>
#include <std_msgs/msg/int32.hpp>
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/bool.hpp> // Ajouté le 16/07 à 15h45
#include <std_srvs/srv/trigger.hpp>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

#include <thread>
#include <chrono>
#include <vector>
#include <array>
#include <cmath>
#include <atomic>
#include <signal.h>

using namespace ur_rtde;

class HapticControlDual : public rclcpp::Node
{
public:
  HapticControlDual()
  : Node("haptic_control_dual"),
    rtde_control("192.168.1.101"),
    rtde_receive("192.168.1.101"),
    velocity(0.1), acceleration(0.1), dt(1.0/125),
    lookahead_time(0.15), gain(500),
    // --- bras expert ---
    expert_button_(0), expert_filter_init_(false),
    expert_filtered_pos_({0.0, 0.0, 0.0}), expert_ref_main_({0.0, 0.0, 0.0}),
    // --- bras apprenant ---
    learner_button_(0), learner_filter_init_(false),
    learner_filtered_pos_({0.0, 0.0, 0.0}), learner_ref_main_({0.0, 0.0, 0.0}),
    // --- partage (robot + blend) ---
    ref_pos_robot_({0.0, 0.0, 0.0}), ref_ori_robot_({0.0, 0.0, 0.0}),
    alpha_nominal_(0.8),
    expert_accum_({0.0, 0.0, 0.0}), learner_accum_({0.0, 0.0, 0.0}), //Ajouté le 16/07
    last_target_z_(0.0394), //Ajouté le 16/07
    manual_scaling_enabled_(false), manual_scaling_(0.1), //Ajouté le 16/07
    expert_held_prev_(false), learner_held_prev_(false),
    was_moving_(false)
  {
    RCLCPP_INFO(this->get_logger(), "Constructeur dual demarre");

    // ----- Souscriptions : positions des deux bras -----
    expert_pos_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
      "/expert/haptic_position", 10,
      std::bind(&HapticControlDual::expert_pos_cb, this, std::placeholders::_1));

    learner_pos_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
      "/learner/haptic_position", 10,
      std::bind(&HapticControlDual::learner_pos_cb, this, std::placeholders::_1));

    // ----- Souscriptions : boutons des deux bras -----
    expert_btn_sub_ = this->create_subscription<std_msgs::msg::Int32>(
      "/expert/button_pressed", 10,
      std::bind(&HapticControlDual::expert_btn_cb, this, std::placeholders::_1));

    learner_btn_sub_ = this->create_subscription<std_msgs::msg::Int32>(
      "/learner/button_pressed", 10,
      std::bind(&HapticControlDual::learner_btn_cb, this, std::placeholders::_1));

    // ----- Force capteur (commune aux deux bras) -----
    force_sub_ = this->create_subscription<geometry_msgs::msg::WrenchStamped>(
      "/force_torque_sensor_broadcaster/wrench", 10,
      std::bind(&HapticControlDual::force_cb, this, std::placeholders::_1));

    // ----- Reglage alpha a chaud -----
    alpha_sub_ = this->create_subscription<std_msgs::msg::Float64>(
      "/alpha", 10,
      std::bind(&HapticControlDual::alpha_cb, this, std::placeholders::_1));

    //Ajouté le 16/07 : scaling manuel (enable + valeur) et publication du scaling reel /////////////
    scaling_enable_sub_ = this->create_subscription<std_msgs::msg::Bool>(
      "/scaling_manual_enable", 10,
      [this](const std_msgs::msg::Bool::SharedPtr msg){ manual_scaling_enabled_ = msg->data; });

    scaling_manual_sub_ = this->create_subscription<std_msgs::msg::Float64>(
      "/scaling_manual", 10,
      [this](const std_msgs::msg::Float64::SharedPtr msg){
        double s = msg->data;
        if (s < 0.0) s = 0.0;
        if (s > 1.0) s = 1.0;
        manual_scaling_ = s;
      });

    scaling_debug_pub_ = this->create_publisher<std_msgs::msg::Float64>("/scaling_debug", 10);
    //////////////////////////////////////////////////////////////////////////////////////////////////

    // ----- Publishers de force : un par bras -----
    expert_force_pub_  = this->create_publisher<geometry_msgs::msg::WrenchStamped>("/expert/haptic_force", 10);
    learner_force_pub_ = this->create_publisher<geometry_msgs::msg::WrenchStamped>("/learner/haptic_force", 10);

    // ----- Pose initiale (identique a haptic_control3) -----
    auto deg2rad = [](double d){ return d * M_PI / 180.0; };
    std::vector<double> init_pose = {
        deg2rad(-15.0),    // J1 Base
        deg2rad(-113.1),   // J2 Shoulder
        deg2rad(93.6),     // J3 Elbow
        deg2rad(-70.5),    // J4 Wrist1
        deg2rad(-90.0),    // J5 Wrist2
        deg2rad(180.0)     // J6 Wrist3
    };

    RCLCPP_INFO(this->get_logger(), "Debut moveJ...");
    rtde_control.moveJ(init_pose, 0.5, 0.5);
    RCLCPP_INFO(this->get_logger(), "moveJ termine.");

    rtde_control.zeroFtSensor();
    RCLCPP_INFO(this->get_logger(), "Tare capteur ATI effectuee - Retour de force actif.");

    // ----- Service de tare manuelle -----
    tare_service_ = this->create_service<std_srvs::srv::Trigger>(
      "/tare_sensor",
      [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>,
             std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
          rtde_control.zeroFtSensor();
          response->success = true;
          response->message = "Tare effectuee";
      });

    // ----- Boucle de controle a 125 Hz -----
    // On separe le calcul de la cible + servoL de l'arrivee des messages :
    // les callbacks ne font que stocker la derniere position/bouton,
    // ce timer calcule la cible blendee et envoie UN seul servoL.
    control_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(8),  // ~125 Hz
      std::bind(&HapticControlDual::control_loop, this));

    RCLCPP_INFO(this->get_logger(), "Initialisation dual complete. alpha_nominal=%.2f", alpha_nominal_.load());
  }

  ~HapticControlDual()
  {
    rtde_control.servoStop();
    rtde_control.stopScript();
  }

private:

  // ============================================================
  //  CALLBACKS : ne font que stocker l'etat (pas de servoL ici)
  // ============================================================

  void expert_pos_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
  {
    apply_filter(msg, expert_filtered_pos_, expert_filter_init_);
  }

  void learner_pos_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
  {
    apply_filter(msg, learner_filtered_pos_, learner_filter_init_);
  }

  void expert_btn_cb(const std_msgs::msg::Int32::SharedPtr msg)
  {
    expert_button_ = msg->data;
    if (expert_button_ == 0) expert_filter_init_ = false; // reinit filtre au relachement
  }

  void learner_btn_cb(const std_msgs::msg::Int32::SharedPtr msg)
  {
    learner_button_ = msg->data;
    if (learner_button_ == 0) learner_filter_init_ = false;
  }

  void alpha_cb(const std_msgs::msg::Float64::SharedPtr msg)
  {
    double a = msg->data;
    if (a < 0.0) a = 0.0;
    if (a > 1.0) a = 1.0;
    alpha_nominal_ = a;
    RCLCPP_INFO(this->get_logger(), "alpha_nominal mis a jour : %.2f", alpha_nominal_.load());
  }

  // Filtre passe-bas EMA sur la position d'un bras (alpha=0.85, identique a haptic_control3)
  void apply_filter(const geometry_msgs::msg::PoseStamped::SharedPtr& msg,
                    std::vector<double>& filtered, bool& initialized)
  {
    const double alpha = 0.85;
    double raw_x = msg->pose.position.x;
    double raw_y = msg->pose.position.y;
    double raw_z = msg->pose.position.z;

    if (!initialized) {
      filtered = {raw_x, raw_y, raw_z};
      initialized = true;
    } else {
      filtered[0] = alpha * filtered[0] + (1.0 - alpha) * raw_x;
      filtered[1] = alpha * filtered[1] + (1.0 - alpha) * raw_y;
      filtered[2] = alpha * filtered[2] + (1.0 - alpha) * raw_z;
    }
  }

  // ============================================================
  //  BOUCLE DE CONTROLE 125 Hz : gating + blend + servoL
  // ============================================================
  void control_loop()
  {
    bool held_expert  = (expert_button_  == 1);
    bool held_learner = (learner_button_ == 1);
    int  n_held = (held_expert ? 1 : 0) + (held_learner ? 1 : 0);

    // ----- Personne ne tient -> robot immobile -----
    if (n_held == 0) {
      if (was_moving_) {
        rtde_control.servoStop();
        was_moving_ = false;
      }
      expert_held_prev_  = false;
      learner_held_prev_ = false;
      return;
    }

    // ----- Detection d'un changement de gating (un bras rejoint ou quitte) -----
    bool gate_changed = (held_expert != expert_held_prev_) ||
                        (held_learner != learner_held_prev_);

    if (gate_changed) {
      // RE-ANCRAGE : robot ref = TCP actuel, refs main des bras actifs = position actuelle
      // -> la cible repart de la pose courante, sans saut, malgre le changement d'alpha.
      std::vector<double> tcp = rtde_receive.getActualTCPPose();
      if (tcp.size() == 6) {
        ref_pos_robot_ = {tcp[0], tcp[1], tcp[2]};
        ref_ori_robot_ = {tcp[3], tcp[4], tcp[5]};
        if (held_expert)  { expert_ref_main_  = expert_filtered_pos_;  expert_accum_  = {0.0, 0.0, 0.0}; } //Ajouté le 16/07
        if (held_learner) { learner_ref_main_ = learner_filtered_pos_; learner_accum_ = {0.0, 0.0, 0.0}; } //Ajouté le 16/07
      }
      expert_held_prev_  = held_expert;
      learner_held_prev_ = held_learner;
    }

    // ----- Alpha effectif selon qui tient -----
    double a;
    if (held_expert && held_learner) a = alpha_nominal_;  // les deux : blend
    else if (held_expert)            a = 1.0;             // expert seul
    else                             a = 0.0;             // apprenant seul

    // ----- Deltas (depuis la ref main de chaque bras), scaling identique a l'original -----
    // const double scaling_factor = 0.1;

    const double z_haut = 0.0394;
    const double z_bas  = 0.0199;

    //std::vector<double> tcp_now = rtde_receive.getActualTCPPose();
    //double z_cur = (tcp_now.size() == 6) ? tcp_now[2] : ref_pos_robot_[2];

    double z_cur = last_target_z_; //Ajouté le 16/07

    double t = (z_cur - z_bas) / (z_haut - z_bas);
    if (t < 0.0) t = 0.0;
    if (t > 1.0) t = 1.0;
    //const double scaling_factor = 0.1 + t * (1.0 - 0.1);

    //Ajouté le 16/07 : soit la rampe automatique, soit la valeur manuelle de l'IHM
    double scaling_factor;
    if (manual_scaling_enabled_.load()) {
      scaling_factor = manual_scaling_.load();
    } else {
      scaling_factor = 0.1 + t * (1.0 - 0.1);
    }

    //Publie le scaling reellement applique (pour affichage IHM)
    {
      std_msgs::msg::Float64 sc_msg;
      sc_msg.data = scaling_factor;
      scaling_debug_pub_->publish(sc_msg);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // Ajouté le 16/07
    if (held_expert) {
      for (int i = 0; i < 3; ++i) {
        double increment = expert_filtered_pos_[i] - expert_ref_main_[i];
        expert_accum_[i] += increment * scaling_factor;
        expert_ref_main_[i] = expert_filtered_pos_[i];
      }
    }
    if (held_learner) {
      for (int i = 0; i < 3; ++i) {
        double increment = learner_filtered_pos_[i] - learner_ref_main_[i];
        learner_accum_[i] += increment * scaling_factor;
        learner_ref_main_[i] = learner_filtered_pos_[i];
      }
    }

    std::array<double,3> dE = { expert_accum_[0], expert_accum_[1], expert_accum_[2] };
    std::array<double,3> dL = { learner_accum_[0], learner_accum_[1], learner_accum_[2] };
    //////////////////

    // ----- Cible blendee (translation seule, orientation figee) -----
    std::array<double,6> target = {
      ref_pos_robot_[0] + a * dE[0] + (1.0 - a) * dL[0],
      ref_pos_robot_[1] + a * dE[1] + (1.0 - a) * dL[1],
      ref_pos_robot_[2] + a * dE[2] + (1.0 - a) * dL[2],
      ref_ori_robot_[0],
      ref_ori_robot_[1],
      ref_ori_robot_[2]
    };

    last_target_z_ = target[2]; //Ajouté le 16/07

    // ----- Securites : workspace + cinematique inverse -----
    if (!in_workspace(target)) {
      RCLCPP_WARN(this->get_logger(), "Consigne hors espace de travail. Arret.");
      rtde_control.servoStop();
      was_moving_ = false;
      return;
    }

    bool ik_ok = rtde_control.getInverseKinematicsHasSolution(
      {target[0], target[1], target[2], target[3], target[4], target[5]});
    if (!ik_ok) {
      RCLCPP_ERROR(this->get_logger(), "Pas de solution IK. Arret.");
      rtde_control.servoStop();
      was_moving_ = false;
      return;
    }

    // ----- servoL : UN seul appel, a cadence fixe -----
    auto t_start = rtde_control.initPeriod();
    rtde_control.servoL({target[0], target[1], target[2], target[3], target[4], target[5]},
                        velocity, acceleration, dt, lookahead_time, gain);
    rtde_control.waitPeriod(t_start);
    was_moving_ = true;
  }

  // ============================================================
  //  FORCE : transform tool0 -> base, publie sur les DEUX bras
  // ============================================================
  void force_cb(const geometry_msgs::msg::WrenchStamped::SharedPtr msg)
  {
    //Ajouté le 20/07 : on ne publie qu'un message sur 5 (~500 Hz -> ~100 Hz)
    if (++force_pub_counter_ < 5) return;
    force_pub_counter_ = 0;

    std::vector<double> tcp_pose = rtde_receive.getActualTCPPose();
    if (tcp_pose.size() != 6) return;

    // axis-angle -> quaternion
    tf2::Vector3 rot_vec(tcp_pose[3], tcp_pose[4], tcp_pose[5]);
    double angle = rot_vec.length();
    tf2::Quaternion q;
    if (angle > 1e-10) {
      tf2::Vector3 axis = rot_vec.normalized();
      q.setRotation(axis, angle);
    } else {
      q = tf2::Quaternion(0, 0, 0, 1);
    }

    // force tool0 -> base
    tf2::Vector3 force_tool(msg->wrench.force.x, msg->wrench.force.y, msg->wrench.force.z);
    tf2::Vector3 force_base = tf2::quatRotate(q, force_tool);

    geometry_msgs::msg::WrenchStamped out_msg;
    out_msg.header.stamp = this->now();
    out_msg.header.frame_id = "base";
    out_msg.wrench.force.x = force_base.x();
    out_msg.wrench.force.y = force_base.y();
    out_msg.wrench.force.z = force_base.z();

    // Les deux bras recoivent la force du robot.
    // (Le couplage expert->apprenant est gere cote Unity.)
    expert_force_pub_->publish(out_msg);
    learner_force_pub_->publish(out_msg);
  }

  // ============================================================
  //  Limites de l'espace de travail (identiques a haptic_control3)
  // ============================================================
  bool in_workspace(const std::array<double,6>& pose)
  {
    const double x_min = -0.38, x_max = 0.10;
    const double y_min = -0.35, y_max = 0.35;
    const double z_min = -0.02, z_max = 0.38;

    if (pose[0] < x_min || pose[0] > x_max) return false;
    if (pose[1] < y_min || pose[1] > y_max) return false;
    if (pose[2] < z_min || pose[2] > z_max) return false;
    return true;
  }

  // ===================== Membres =====================
  RTDEControlInterface rtde_control;
  RTDEReceiveInterface rtde_receive;
  double velocity, acceleration, dt, lookahead_time, gain;

  // --- bras expert ---
  int    expert_button_;
  bool   expert_filter_init_;
  std::vector<double> expert_filtered_pos_;
  std::vector<double> expert_ref_main_;

  // --- bras apprenant ---
  int    learner_button_;
  bool   learner_filter_init_;
  std::vector<double> learner_filtered_pos_;
  std::vector<double> learner_ref_main_;

  // --- partage (robot + blend) ---
  std::vector<double> ref_pos_robot_;
  std::vector<double> ref_ori_robot_;
  std::atomic<double> alpha_nominal_;

  // Ajouté le 16/07
  std::vector<double> expert_accum_;
  std::vector<double> learner_accum_;

  double last_target_z_;

  std::atomic<bool> manual_scaling_enabled_;
  std::atomic<double> manual_scaling_;
  int force_pub_counter_ = 0; //Ajouté le 20/07
  //////////////////
  
  bool expert_held_prev_;
  bool learner_held_prev_;
  bool was_moving_;

  // --- ROS ---
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr expert_pos_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr learner_pos_sub_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr expert_btn_sub_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr learner_btn_sub_;
  rclcpp::Subscription<geometry_msgs::msg::WrenchStamped>::SharedPtr force_sub_;
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr alpha_sub_;

  //Ajouté le 16/07/////////////////////////////////////////////////////////////
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr scaling_enable_sub_;
  rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr scaling_manual_sub_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr scaling_debug_pub_;

  /////////////////////////////////////////////////////////////////////////////

  rclcpp::Publisher<geometry_msgs::msg::WrenchStamped>::SharedPtr expert_force_pub_;
  rclcpp::Publisher<geometry_msgs::msg::WrenchStamped>::SharedPtr learner_force_pub_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr tare_service_;
  rclcpp::TimerBase::SharedPtr control_timer_;
};

// ===================== main (signal handling + retry, comme l'original) =====================
std::shared_ptr<HapticControlDual> g_node = nullptr;

void signal_handler(int signum)
{
  RCLCPP_INFO(rclcpp::get_logger("haptic_control_dual"), "Signal recu (%d), deconnexion propre...", signum);
  if (g_node) g_node.reset();
  rclcpp::shutdown();
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGABRT, signal_handler);
  signal(SIGSEGV, signal_handler);

  while (rclcpp::ok()) {
    try {
      g_node = std::make_shared<HapticControlDual>();
      rclcpp::spin(g_node);   // executeur mono-thread : callbacks + timer serialises (pas de mutex requis)
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