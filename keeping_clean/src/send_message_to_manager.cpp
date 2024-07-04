#include "send_message_to_manager.h"

SendMessageToManager::SendMessageToManager(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus SendMessageToManager::tick()
{
  auto message = getInput<std::string>("message");

  RCLCPP_INFO(node_ptr_->get_logger(), "SendMessageToManager: %s", message.value().c_str());
  return BT::NodeStatus::SUCCESS;
}
