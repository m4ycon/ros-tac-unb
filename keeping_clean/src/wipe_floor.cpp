#include "wipe_floor.h"

WipeFloor::WipeFloor(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus WipeFloor::tick()
{
  return BT::NodeStatus::SUCCESS;
}
