#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


class RobotControl : public rclcpp::Node {
public:
  RobotControl() : Node("robot_control"), x_velocity_(0.0), z_velocity_(0.0), wait_publish_(false) {
    publisher_ = this->create_publisher<std_msgs::msg::String>(
      "/urscript_interface/script_command", 10);
    
    // boucle de lecture du clavier
    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(25),
      std::bind(&RobotControl::keyboard, this));

    // configurer le terminal pour la lecture non-bloquante des touches
    tcgetattr(STDIN_FILENO, &oldt_);
    newt_ = oldt_;
    newt_.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt_);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  }

  ~RobotControl() {
    // restaurer les paramètres du terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt_);
  }

private:
  void keyboard() {
    char c;
    bool key_pressed = false;

    // Lire l'entrée clavier
    if (read(STDIN_FILENO, &c, 1) > 0) {
      // Flèches gauche et droite
      if (c == '\033') {
        char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0) {
          if (seq[1] == 'C') x_velocity_ = 0.01;   // droite
          else if (seq[1] == 'D') x_velocity_ = -0.01; // gauche
          else if (seq[1] == 'A') z_velocity_ = 0.01; // haut
          else if (seq[1] == 'B') z_velocity_ = -0.01; // bas
          key_pressed = true;
        }
      }
    }

    // arrêt du mouvement
    if (!key_pressed) {
      x_velocity_ = 0.0, z_velocity_ = 0.0;
    }

    if((x_velocity_ != 0.0 || z_velocity_ != 0.0)  && !wait_publish_) {
      script_command(x_velocity_, z_velocity_);
    }

  }
    void script_command(float x, float z) {
        wait_publish_ = true;
        auto msg = std_msgs::msg::String();
        msg.data = "movel(pose_add(get_actual_tcp_pose(), p[" + std::to_string(x) +  ", 0.0," + std::to_string(z) + ", 0, 0, 0]), a=0.1, v=0.1)";
        publisher_->publish(msg);
        wait_timer_ = this->create_wall_timer(
          std::chrono::milliseconds(1000),
          std::bind(&RobotControl::wait_for_publish, this));


    }

  void wait_for_publish() {
    wait_publish_ = false;
    wait_timer_.reset();
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_, wait_timer_;
  struct termios oldt_, newt_;
  float x_velocity_, z_velocity_;
  bool wait_publish_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RobotControl>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}