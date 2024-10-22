#include "move_furniture.h"

MoveFurniture::MoveFurniture(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus MoveFurniture::tick()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "MoveFurniture");
  return BT::NodeStatus::SUCCESS;
}
