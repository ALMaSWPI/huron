# include "huron_ros2/robot.h"

namespace huron {
namespace ros2 {

void Robot::Configure() {
  rclcpp::init(0, 0);
  rclcpp::spin(std::make_shared<HuronNode>());
  rclcpp::shutdown();
}

void Robot::Terminate() {
  rclcpp::shutdown();
}

bool Robot::Move(std::vector<float> values) {
  // Publishing to the topic
  auto message = sensor_msgs::msg::JointState();
  for (int i = 0; i < 3; i++){
    message.position[i] = values[i];
  }
  RCLCPP_INFO(this->node.get_logger(), "Publishing Position:");
  //RCLCPP_INFO(message.position);
  // this->node.publisher_joints_->publish(message);
  return true;
}

bool Robot::Stop() {
  // Publishing to the topic
  auto message = sensor_msgs::msg::JointState();
  for (int i = 0; i < 3; i++){
    message.effort[i] = 0;
    message.velocity[i] = 0;
  }
  RCLCPP_INFO(this->node.get_logger(), "Terminated'");
  // this->node.publisher_joints_->publish(message);
  return true;
}

}  // namespace ros2
}  // namespace huron
