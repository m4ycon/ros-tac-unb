#include <rclcpp/rclcpp.hpp>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/condition_node.h"
#include "rclcpp_action/rclcpp_action.hpp"

#include <string>

class Sleep : public BT::SyncActionNode
{
public:
  Sleep(const std::string &name,
                  const BT::NodeConfiguration &config,
                  rclcpp::Node::SharedPtr node_ptr);

  // Method overrides
  BT::NodeStatus tick() override;

  static BT::PortsList providedPorts()
  {
    return BT::PortsList{BT::InputPort<int>("msec")};
  }
  

private:
  rclcpp::Node::SharedPtr node_ptr_;
};
