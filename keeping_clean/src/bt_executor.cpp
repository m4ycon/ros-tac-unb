#include "bt_executor.h"
#include "publisher_node.cpp"
#include "subscriber_node.cpp"

#include "abort_mission.cpp"
#include "check_battery.cpp"
#include "check_equipments.cpp"
#include "go_to_destination.cpp"
#include "is_room_free.cpp"
#include "move_furniture.cpp"
#include "pick_equipments.cpp"
#include "send_message_to_manager.cpp"
#include "sleep.cpp"
#include "station_dock.cpp"
#include "station_undock.cpp"
#include "sterilize_furniture.cpp"
#include "time_to_complete.cpp"
#include "vacuum_floor.cpp"
#include "wipe_floor.cpp"

BTExecutor::BTExecutor(const std::string &node_name) : rclcpp::Node(node_name)
{
  this->declare_parameter("bt", rclcpp::PARAMETER_STRING);
  this->declare_parameter("tick_rate_ms", rclcpp::PARAMETER_INTEGER);

  this->declare_parameter("ttc", rclcpp::PARAMETER_INTEGER);
  this->declare_parameter("has_equipments", rclcpp::PARAMETER_BOOL);
  this->declare_parameter("is_room_free", rclcpp::PARAMETER_BOOL);
  this->declare_parameter("recharge_x", rclcpp::PARAMETER_DOUBLE);
  this->declare_parameter("recharge_y", rclcpp::PARAMETER_DOUBLE);
  this->declare_parameter("room_x", rclcpp::PARAMETER_DOUBLE);
  this->declare_parameter("room_y", rclcpp::PARAMETER_DOUBLE);
  this->declare_parameter("storage_x", rclcpp::PARAMETER_DOUBLE);
  this->declare_parameter("storage_y", rclcpp::PARAMETER_DOUBLE);

  RCLCPP_INFO(get_logger(), "Started BT Executor");
}

void BTExecutor::setup()
{
  RCLCPP_INFO(get_logger(), "Started BT Setup");
  create_behavior_tree();
  RCLCPP_INFO(get_logger(), "Created BT Successfully");

  rclcpp::Parameter int_param = this->get_parameter("tick_rate_ms");
  int tick_rate_ms = int_param.as_int();
  auto timer_period = std::chrono::duration<int, std::ratio<1, 1000>>(tick_rate_ms);
  timer_ = this->create_wall_timer(
      timer_period,
      std::bind(&BTExecutor::update_behavior_tree, this));

  rclcpp::spin(shared_from_this());
}

void BTExecutor::halt_behavior_tree()
{
  timer_->cancel();
  rclcpp::shutdown();
}

void BTExecutor::update_behavior_tree()
{
  BT::NodeStatus tree_status = tree_.tickRoot();
  if (tree_status == BT::NodeStatus::FAILURE)
  {
    RCLCPP_INFO(get_logger(), "BT Ended with FAILURE");
    halt_behavior_tree();
  }
  else if (tree_status == BT::NodeStatus::SUCCESS)
  {
    RCLCPP_INFO(get_logger(), "BT Ended with SUCCESS");
    halt_behavior_tree();
  }
}

void BTExecutor::register_nav2_plugins()
{
  const std::string plugins_path = ament_index_cpp::get_package_share_directory("keeping_clean") + "/behavior_trees/plugins.txt";
  std::ifstream plugin_file;
  plugin_file.open(plugins_path);

  BT::SharedLibrary loader;

  if (plugin_file.is_open())
    for (std::string plugin; std::getline(plugin_file, plugin);)
      factory_.registerFromPlugin(loader.getOSName(plugin));

  plugin_file.close();
}

void BTExecutor::register_nodes()
{
  registerNode<PublisherNode>("Publisher");
  registerNode<SubscriberNode>("Subscriber");

  registerNode<AbortMission>("AbortMission");
  registerNode<CheckBattery>("CheckBattery");
  registerNode<CheckEquipments>("CheckEquipments");
  registerNode<GoToDestination>("GoToDestination");
  registerNode<IsRoomFree>("IsRoomFree");
  registerNode<MoveFurniture>("MoveFurniture");
  registerNode<PickEquipments>("PickEquipments");
  registerNode<SendMessageToManager>("SendMessageToManager");
  registerNode<Sleep>("Sleep");
  registerNode<StationDock>("StationDock");
  registerNode<StationUndock>("StationUndock");
  registerNode<SterilizeFurniture>("SterilizeFurniture");
  registerNode<TimeToComplete>("TimeToComplete");
  registerNode<VacuumFloor>("VacuumFloor");
  registerNode<WipeFloor>("WipeFloor");
}

void BTExecutor::register_blackboard_data()
{
  tree_.rootBlackboard()->set("ttc", (int)get_parameter("ttc").as_int());
  tree_.rootBlackboard()->set("has_equipments", get_parameter("has_equipments").as_bool());
  tree_.rootBlackboard()->set("is_room_free", get_parameter("is_room_free").as_bool());
  tree_.rootBlackboard()->set("recharge_x", get_parameter("recharge_x").as_double());
  tree_.rootBlackboard()->set("recharge_y", get_parameter("recharge_y").as_double());
  tree_.rootBlackboard()->set("room_x", get_parameter("room_x").as_double());
  tree_.rootBlackboard()->set("room_y", get_parameter("room_y").as_double());
  tree_.rootBlackboard()->set("storage_x", get_parameter("storage_x").as_double());
  tree_.rootBlackboard()->set("storage_y", get_parameter("storage_y").as_double());
}

void BTExecutor::create_behavior_tree()
{
  rclcpp::Parameter str_param = this->get_parameter("bt");
  std::string tree_xml = str_param.as_string();

  // Registering Custom BT Nodes
  RCLCPP_INFO(get_logger(), "Registering Nodes");
  register_nodes();

  // Registering nav2 nodes
  RCLCPP_INFO(get_logger(), "Registering Nav2 Plugins");
  register_nav2_plugins();

  // Creating tree from xml
  RCLCPP_INFO(get_logger(), "Creating Tree %s", tree_xml.c_str());
  tree_ = factory_.createTreeFromFile(tree_xml);

  // Setting blackboard values
  RCLCPP_INFO(get_logger(), "Setting Blackboard Data");
  register_blackboard_data();
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<BTExecutor>("bt_executor");
  node->setup();

  return 0;
}
