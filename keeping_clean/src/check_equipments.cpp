#include "check_equipments.h"

CheckEquipments::CheckEquipments(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::ConditionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus CheckEquipments::tick()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "CheckEquipments");
  return BT::NodeStatus::SUCCESS;
}
