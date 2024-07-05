#include "time_to_complete.h"

TimeToComplete::TimeToComplete(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus TimeToComplete::tick()
{
  auto ttc = getInput<int>("ttc");
  RCLCPP_INFO(node_ptr_->get_logger(), "TimeToComplete %ds", ttc.value());

  return BT::NodeStatus::SUCCESS;
}
