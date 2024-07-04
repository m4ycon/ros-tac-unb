#include "station_undock.h"

StationUndock::StationUndock(const std::string &name, const BT::NodeConfiguration &config, rclcpp::Node::SharedPtr node_ptr)
    : BT::StatefulActionNode(name, config), node_ptr_(node_ptr)
{
  action_client_ptr_ = rclcpp_action::create_client<Undock>(node_ptr_, "undock");
  done_flag_ = false;

  auto qos = rclcpp::SystemDefaultsQoS();
  qos.best_effort();
  subscriber_ptr_ = node_ptr->create_subscription<DockStatus>(
      "/dock_status",
      qos,
      std::bind(&StationUndock::dock_status_callback, this, std::placeholders::_1));
}

BT::NodeStatus StationUndock::onStart()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "StationUndock");

  auto goal_msg = Undock::Goal();

  auto send_goal_options = rclcpp_action::Client<Undock>::SendGoalOptions();
  send_goal_options.result_callback = std::bind(&StationUndock::undock_callback, this, std::placeholders::_1);

  // Send pose
  done_flag_ = false;
  for (int i = 0; i < 5; i++)
  {
    action_client_ptr_->async_send_goal(goal_msg, send_goal_options);
    sleep(1);
  }

  RCLCPP_INFO(node_ptr_->get_logger(), "Sent Goal to undock");
  return BT::NodeStatus::RUNNING;
}

BT::NodeStatus StationUndock::onRunning()
{
  if (done_flag_ || !is_docked_)
  {
    RCLCPP_INFO(node_ptr_->get_logger(), "Undocked");
    return BT::NodeStatus::SUCCESS;
  }
  return BT::NodeStatus::RUNNING;
}

void StationUndock::undock_callback(const GoalHandleUndock::WrappedResult &result)
{
  if (result.code == rclcpp_action::ResultCode::SUCCEEDED)
    done_flag_ = true;
}

void StationUndock::dock_status_callback(const DockStatus::SharedPtr msg)
{
  is_docked_ = msg->is_docked;
}
