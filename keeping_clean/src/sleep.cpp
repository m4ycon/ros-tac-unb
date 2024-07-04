#include "sleep.h"

Sleep::Sleep(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus Sleep::tick()
{
  auto msec = getInput<int>("msec");
  rclcpp::sleep_for(std::chrono::milliseconds(msec.value()));
  return BT::NodeStatus::SUCCESS;
}
