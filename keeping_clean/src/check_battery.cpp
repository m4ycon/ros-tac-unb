#include "check_battery.h"

CheckBattery::CheckBattery(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::StatefulActionNode(name, config), node_ptr_(node_ptr)
{
  auto qos = rclcpp::SystemDefaultsQoS();
  qos.best_effort();
  subscriber_ptr_ = node_ptr->create_subscription<sensor_msgs::msg::BatteryState>(
      "/battery_state",
      qos,
      std::bind(&CheckBattery::update_msg, this, std::placeholders::_1));
}

BT::NodeStatus CheckBattery::onStart()
{
  auto percentage = msg_.percentage * 100;

  if (percentage == 0) {
    RCLCPP_INFO(node_ptr_->get_logger(), "Waiting for battery message");
    return BT::NodeStatus::RUNNING;
  }

  RCLCPP_INFO(node_ptr_->get_logger(), "CheckBattery (%f%%)", percentage);
  if (percentage < 15)
  {
    RCLCPP_INFO(node_ptr_->get_logger(), "Battery low");
    return BT::NodeStatus::FAILURE;
  }

  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CheckBattery::onRunning()
{
  auto percentage = msg_.percentage * 100;

  if (percentage == 0) {
    RCLCPP_INFO(node_ptr_->get_logger(), "Waiting for battery message");
    return BT::NodeStatus::RUNNING;
  }

  RCLCPP_INFO(node_ptr_->get_logger(), "CheckBattery (%f%%)", percentage);
  if (percentage < 15)
  {
    RCLCPP_INFO(node_ptr_->get_logger(), "Battery low");
    return BT::NodeStatus::FAILURE;
  }

  return BT::NodeStatus::SUCCESS;
}

void CheckBattery::update_msg(const sensor_msgs::msg::BatteryState new_msg)
{
  msg_ = new_msg;
}
