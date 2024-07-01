#include "rclcpp/rclcpp.hpp"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/condition_node.h"
#include "rclcpp_action/rclcpp_action.hpp"
#include "nav2_msgs/action/navigate_to_pose.hpp"

#include <string>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

class SendMessageToManager : public BT::SyncActionNode
{
public:
  SendMessageToManager(const std::string &name,
                       const BT::NodeConfiguration &config,
                       rclcpp::Node::SharedPtr node_ptr);

  // Method overrides
  BT::NodeStatus tick() override;

  static BT::PortsList providedPorts()
  {
    return BT::PortsList{BT::InputPort<std::string>("message")};
  }

private:
  rclcpp::Node::SharedPtr node_ptr_;
};
