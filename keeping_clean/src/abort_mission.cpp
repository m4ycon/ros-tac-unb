#include "abort_mission.h"

AbortMission::AbortMission(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus AbortMission::tick()
{
  return BT::NodeStatus::SUCCESS;
}
