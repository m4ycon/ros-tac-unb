#include "pick_equipments.h"

PickEquipments::PickEquipments(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus PickEquipments::tick()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "PickEquipments");
  setOutput("has_equipments", true);
  return BT::NodeStatus::SUCCESS;
}
