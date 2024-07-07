#include "rclcpp/rclcpp.hpp"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/utils/shared_library.h"
#include "ament_index_cpp/get_package_share_directory.hpp"

#include <string>
#include <fstream>
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class BTExecutor : public rclcpp::Node
{
public:
  explicit BTExecutor(const std::string &node_name);
  void setup();
  void create_behavior_tree();
  void update_behavior_tree();
  void halt_behavior_tree();

  void register_nav2_plugins();
  void register_nodes();
  void register_blackboard_data();

private:
  BT::BehaviorTreeFactory factory_;
  rclcpp::TimerBase::SharedPtr timer_;
  BT::Tree tree_;

  template <typename T>
  inline void registerNode(const std::string &name)
  {

    BT::NodeBuilder builder = [=](const std::string &name, const BT::NodeConfiguration &config)
    {
      return std::make_unique<T>(name, config, shared_from_this());
    };
    factory_.registerBuilder<T>(name, builder);
  }
};
