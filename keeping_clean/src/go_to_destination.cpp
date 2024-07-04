#include "go_to_destination.h"

GoToDestination::GoToDestination(const std::string &name,
                                 const BT::NodeConfiguration &config,
                                 rclcpp::Node::SharedPtr node_ptr)
    : BT::StatefulActionNode(name, config), node_ptr_(node_ptr)
{
  action_client_ptr_ = rclcpp_action::create_client<NavigateToPose>(node_ptr_, "navigate_to_pose");
  done_flag_ = false;
}

BT::NodeStatus GoToDestination::onStart()
{
  // Make pose
  auto goal_msg = NavigateToPose::Goal();
  auto x = getInput<double>("x").value();
  auto y = getInput<double>("y").value();
  goal_msg.pose.header.frame_id = "map";
  goal_msg.pose.pose.position.x = x;
  goal_msg.pose.pose.position.y = y;

  // Calculate quaternion from yaw
  tf2::Quaternion q;
  q.setRPY(0, 0, 0);
  q.normalize();
  goal_msg.pose.pose.orientation = tf2::toMsg(q);

  // Setup action client
  auto send_goal_options = rclcpp_action::Client<NavigateToPose>::SendGoalOptions();
  send_goal_options.result_callback = std::bind(&GoToDestination::nav_to_pose_callback, this, std::placeholders::_1);

  // Send pose
  RCLCPP_INFO(node_ptr_->get_logger(), "GoToDestination: sending goal (%f, %f)\n", x, y);
  done_flag_ = false;
  for (int i = 0; i < 5; i++)
  {
    action_client_ptr_->async_send_goal(goal_msg, send_goal_options);
    sleep(1);
  }

  RCLCPP_INFO(node_ptr_->get_logger(), "GoToDestination: sent goal (%f, %f)\n", x, y);
  return BT::NodeStatus::RUNNING;
}

BT::NodeStatus GoToDestination::onRunning()
{
  RCLCPP_INFO(node_ptr_->get_logger(), "GoToDestination: onRunning\n");
  if (!done_flag_) return BT::NodeStatus::RUNNING;

  auto x = getInput<double>("x").value();
  auto y = getInput<double>("y").value();
  RCLCPP_INFO(node_ptr_->get_logger(), "GoToDestination: goal reached (%f, %f)\n", x, y);
  return BT::NodeStatus::SUCCESS;
}

void GoToDestination::nav_to_pose_callback(const GoalHandleNav::WrappedResult &result)
{
  // If there is a result, we consider navigation completed.
  if (result.code == rclcpp_action::ResultCode::SUCCEEDED)
    done_flag_ = true;
}
