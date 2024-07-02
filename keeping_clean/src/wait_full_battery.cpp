#include "wait_full_battery.h"

WaitFullBattery::WaitFullBattery(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus WaitFullBattery::tick()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "WaitFullBattery");
  return BT::NodeStatus::SUCCESS;
}
