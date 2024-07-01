#include "is_room_free.h"

IsRoomFree::IsRoomFree(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::ConditionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus IsRoomFree::tick()
{
  return BT::NodeStatus::SUCCESS;
}
