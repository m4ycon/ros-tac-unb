#include <rclcpp/rclcpp.hpp>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/condition_node.h"
#include "rclcpp_action/rclcpp_action.hpp"
#include <sensor_msgs/msg/battery_state.hpp>
#include "irobot_create_msgs/action/dock.hpp"
#include "irobot_create_msgs/msg/dock_status.hpp"

#include <string>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

class StationDock : public BT::StatefulActionNode
{
public:
  StationDock(const std::string &name,
              const BT::NodeConfiguration &config,
              rclcpp::Node::SharedPtr node_ptr);

  using Dock = irobot_create_msgs::action::Dock;
  using GoalHandleDock = rclcpp_action::ClientGoalHandle<Dock>;

  using DockStatus = irobot_create_msgs::msg::DockStatus;

  // Method overrides
  BT::NodeStatus onStart() override;
  BT::NodeStatus onRunning() override;
  void onHalted() override {};

  void dock_callback(const GoalHandleDock::WrappedResult &result);
  void dock_status_callback(const DockStatus::SharedPtr msg);

private:
  rclcpp::Node::SharedPtr node_ptr_;

  rclcpp_action::Client<Dock>::SharedPtr action_client_ptr_;
  bool done_flag_;

  rclcpp::Subscription<DockStatus>::SharedPtr subscriber_ptr_;
  bool is_docked_;
};
