#include "station_dock.h"

StationDock::StationDock(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::StatefulActionNode(name, config), node_ptr_(node_ptr)
{
  action_client_ptr_ = rclcpp_action::create_client<Dock>(node_ptr_, "dock");
  done_flag_ = false;
}

BT::NodeStatus StationDock::onStart()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "StationDock");

  auto goal_msg = Dock::Goal();

  auto send_goal_options = rclcpp_action::Client<Dock>::SendGoalOptions();
  send_goal_options.result_callback = std::bind(&StationDock::dock_callback, this, std::placeholders::_1);

  // Send pose
  done_flag_ = false;
  for (int i = 0; i < 5; i++)
  {
    action_client_ptr_->async_send_goal(goal_msg, send_goal_options);
    sleep(1);
  }

  RCLCPP_INFO(node_ptr_->get_logger(), "Sent Goal to dock");
  return BT::NodeStatus::RUNNING;
}

BT::NodeStatus StationDock::onRunning()
{
  if (done_flag_)
  {
    RCLCPP_INFO(node_ptr_->get_logger(), "Docked");
    return BT::NodeStatus::SUCCESS;
  }
  return BT::NodeStatus::RUNNING;
}

void StationDock::dock_callback(const GoalHandleDock::WrappedResult &result)
{
  if (result.code == rclcpp_action::ResultCode::SUCCEEDED)
    done_flag_ = true;
}
