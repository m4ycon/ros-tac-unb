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

## How to run

To run gazebo:

```bash
ros2 launch turtlebot4_ignition_bringup turtlebot4_ignition.launch.py slam:=true nav2:=true rviz:=true
```

To run the behavior tree:

```bash
cd keeping_clean
colcon build 
source install/setup.zsh
cmake . && make
ros2 launch keeping_clean execute_bt.launch.py bt:="./behavior_trees/keeping_clean.xml" blackboard:="./behavior_trees/blackboard.json"
```
