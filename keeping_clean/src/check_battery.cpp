#include "check_battery.h"

CheckBattery::CheckBattery(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::ConditionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus CheckBattery::tick()
{
  return BT::NodeStatus::SUCCESS;
}