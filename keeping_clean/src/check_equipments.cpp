#include "check_equipments.h"

CheckEquipments::CheckEquipments(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::ConditionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus CheckEquipments::tick()
{
  auto has_equipments = getInput<bool>("has_equipments");
  if (!has_equipments.value())
  {
    RCLCPP_INFO(node_ptr_->get_logger(), "Equipments are NOT OK");
    return BT::NodeStatus::FAILURE;
  }

  RCLCPP_INFO(node_ptr_->get_logger(), "Equipments are OK");
  return BT::NodeStatus::SUCCESS;
}
