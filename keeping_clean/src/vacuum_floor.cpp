#include "vacuum_floor.h"

VacuumFloor::VacuumFloor(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::SyncActionNode(name, config), node_ptr_(node_ptr)
{
}

BT::NodeStatus VacuumFloor::tick()
{
  return BT::NodeStatus::SUCCESS;
}
