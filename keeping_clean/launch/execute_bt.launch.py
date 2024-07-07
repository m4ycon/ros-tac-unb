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
    DeclareLaunchArgument('tick_rate_ms', default_value="500",
                          description='Rate in milliseconds between ticks'),

    DeclareLaunchArgument("ttc", default_value="0"),
    DeclareLaunchArgument("has_equipments", default_value="False"),
    DeclareLaunchArgument("is_room_free", default_value="True"),
    DeclareLaunchArgument("recharge_x", default_value="0.0"),
    DeclareLaunchArgument("recharge_y", default_value="0.0"),
    DeclareLaunchArgument("room_x", default_value="0.0"),
    DeclareLaunchArgument("room_y", default_value="-3.0"),
    DeclareLaunchArgument("storage_x", default_value="-1.0"),
    DeclareLaunchArgument("storage_y", default_value="1.0"),
]


def generate_launch_description():
  execute_bt_cmd = Node(
      package="keeping_clean",
      executable="bt_executor",
      name="bt_executor",
      parameters=[{
          "bt": LaunchConfiguration('bt'),
          "tick_rate_ms": LaunchConfiguration("tick_rate_ms"),

          "ttc": LaunchConfiguration("ttc"),
          "has_equipments": LaunchConfiguration("has_equipments"),
          "is_room_free": LaunchConfiguration("is_room_free"),
          "recharge_x": LaunchConfiguration("recharge_x"),
          "recharge_y": LaunchConfiguration("recharge_y"),
          "room_x": LaunchConfiguration("room_x"),
          "room_y": LaunchConfiguration("room_y"),
          "storage_x": LaunchConfiguration("storage_x"),
          "storage_y": LaunchConfiguration("storage_y"),
      }],
  )

  ld = LaunchDescription(ARGUMENTS)
  ld.add_action(execute_bt_cmd)

  return ld
