#include "is_room_free.h"

IsRoomFree::IsRoomFree(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus IsRoomFree::tick()
{
  auto is_room_free = getInput<bool>("is_room_free");
  if (!is_room_free.value())
  {
    RCLCPP_INFO(node_ptr_->get_logger(), "Room is not free");
    return BT::NodeStatus::FAILURE;
  }

  RCLCPP_INFO(node_ptr_->get_logger(), "Room is free");
  return BT::NodeStatus::SUCCESS;
}
