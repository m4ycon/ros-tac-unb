#include "check_battery.h"

CheckBattery::CheckBattery(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::ConditionNode(name, config), node_ptr_(node_ptr)
{
  auto qos = rclcpp::SystemDefaultsQoS();
  qos.best_effort();
  subscriber_ptr_ = node_ptr->create_subscription<sensor_msgs::msg::BatteryState>(
      "/battery_state",
      qos,
      std::bind(&CheckBattery::update_msg, this, std::placeholders::_1));
}

BT::NodeStatus CheckBattery::tick()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "CheckBattery");

  if (msg_.percentage < 15)
  {
    RCLCPP_INFO(node_ptr_->get_logger(), "Battery low: %f", msg_.percentage);
    return BT::NodeStatus::FAILURE;
  }

  return BT::NodeStatus::SUCCESS;
}

void CheckBattery::update_msg(const sensor_msgs::msg::BatteryState new_msg)
{
  msg_ = new_msg;
}
