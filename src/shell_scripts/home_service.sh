#!/bin/sh

xterm  -e  " source devel/setup.bash;  roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find add_markers)/../worlds/dragon.world" &
sleep 10
xterm -e " roslaunch add_markers view_homeServiceRobot.launch" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find add_markers)/../worlds/map.yaml"  &
sleep 5
xterm -e "  rosrun add_markers add_markers" &
sleep 2
xterm -e "  rosrun pick_objects pick_objects"
