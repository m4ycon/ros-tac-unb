#include "abort_mission.h"

AbortMission::AbortMission(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus AbortMission::tick()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "AbortMission");
  return BT::NodeStatus::SUCCESS;
}
