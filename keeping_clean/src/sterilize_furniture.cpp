#include "sterilize_furniture.h"

SterilizeFurniture::SterilizeFurniture(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus SterilizeFurniture::tick()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "SterilizeFurniture");
  return BT::NodeStatus::SUCCESS;
}
