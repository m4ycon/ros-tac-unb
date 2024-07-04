## Mission

Our selected mission is the Keeping Clean ([taken from](https://github.com/Askarpour/RoboMAX/blob/main/Exemplars.csv)).

Every room that reaches more than 1 cfu/cm$^2$ of Staphylococcus aureus must be cleaned within the next 30 minutes. The assigned robot must check if it has all the resources to fulfill the tasks.

In the case of **missing equipment**, the robot must go to the storage room to collect the equipment or assign the go-to-storage task to a colleague.

As the robot reaches the room, it must check if it is **occupied**. If the room is occupied, a message should be sent to the manager and the mission aborted. Otherwise, the robot should enter the room and mark it as occupied.

The cleaning task must be performed in order:
1. Change the furniture's covers, towels, and clothes;
2. Vacuum the floor, moving furniture when necessary;
3. Wipe the floor;
4. Sterilize all furniture and equipment in the room.

In case of failure in performing any of the steps, it immediately warns the sector manager, but does not stop executing the mission.

All personal equipment (sensors, probes) found that do not originally pertain to the room must be removed from the room. If non-identified objects are found in the room, the robot should take a photo, report it to the manager, and if collectible, take it out of the room.

In case of a **low battery**, recharge it and come back to finish the task.

## Helper Commands

```bash

--- para rodar

ros2 launch turtlebot4_ignition_bringup turtlebot4_ignition.launch.py slam:=true nav2:=true

source install/setup.zsh # pelo menos uma vez após o colcon build

colcon build && cmake . && make && \
ros2 launch keeping_clean execute_bt.launch.py bt:="./behavior_trees/keeping_clean.xml"


--- comandos comuns

source /opt/ros/humble/setup.zsh

ros2 pkg create --build-type ament_python --node-name my_node_name my_package_name


ros2 launch turtlebot4_ignition_bringup turtlebot4_ignition.launch.py slam:=true rviz:=true nav2:=true

ros2 launch turtlebot4_ignition_bringup turtlebot4_ignition.launch.py slam:=true nav2:=true

source install/setup.zsh

colcon build
cmake . && make
ros2 launch keeping_clean execute_bt.launch.py bt:="./behavior_trees/keeping_clean.xml"


--- problemas em ver o scan no rviz

cd /opt/ros/humble/share/irobot_create_description/urdf/
sudo code create3.urdf.xacro
# substitui ogre por ogre2

---

ros2 run nav2_map_server map_saver_cli -f "my_map"

---

sudo apt install ros-$ROS_DISTRO-turtle-tf2-py ros-$ROS_DISTRO-tf2-tools ros-$ROS_DISTRO-tf-transformations

sudo wget https://packages.osrfoundation.org/gazebo.gpg -O /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null
sudo apt-get update
sudo apt-get install ignition-fortress

```
