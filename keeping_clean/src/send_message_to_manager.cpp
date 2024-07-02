#include "send_message_to_manager.h"

SendMessageToManager::SendMessageToManager(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus SendMessageToManager::tick()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "SendMessageToManager");
  return BT::NodeStatus::SUCCESS;
}
