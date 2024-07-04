#include <rclcpp/rclcpp.hpp>
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/condition_node.h"
#include "rclcpp_action/rclcpp_action.hpp"
#include <sensor_msgs/msg/battery_state.hpp>

#include <string>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

class CheckBattery : public BT::StatefulActionNode
{
public:
  CheckBattery(const std::string &name,
                  const BT::NodeConfiguration &config,
                  rclcpp::Node::SharedPtr node_ptr);

  // Method overrides
  BT::NodeStatus onStart() override;
  BT::NodeStatus onRunning() override;
  void onHalted() override {};

  void update_msg(const sensor_msgs::msg::BatteryState new_msg);

private:
  rclcpp::Node::SharedPtr node_ptr_;
  rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr subscriber_ptr_;
  sensor_msgs::msg::BatteryState msg_;
};
