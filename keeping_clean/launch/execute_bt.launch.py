import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration


pkg_keeping_clean = get_package_share_directory('keeping_clean')
ARGUMENTS = [
    DeclareLaunchArgument('bt',
                          description='Behavior Tree XML to execute'),
    DeclareLaunchArgument('blackboard',
                          description='Blackboard json file'),
    DeclareLaunchArgument('tick_rate_ms', default_value="500",
                          description='Rate in milliseconds between ticks'),
]


def generate_launch_description():
  execute_bt_cmd = Node(
      package="keeping_clean",
      executable="bt_executor",
      name="bt_executor",
      parameters=[{
          "bt": LaunchConfiguration('bt'),
          "blackboard": LaunchConfiguration("blackboard"),
          "tick_rate_ms": LaunchConfiguration("tick_rate_ms"),
      }],
  )

  ld = LaunchDescription(ARGUMENTS)
  ld.add_action(execute_bt_cmd)

  return ld
