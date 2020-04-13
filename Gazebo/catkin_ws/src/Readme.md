# Simulation Setup Notes

Followed this tutorial: https://www.generationrobots.com/blog/en/robotic-simulation-scenarios-with-gazebo-and-ros/

Note: this tutorial is for an ROS Hydro and this repo uses ROS Melodic and so some changes have been made. Additionally, when installing packages (e.g. controller drivers) ensure the melodic versions are installed. The Github for this tutorial can be found at: https://github.com/HumaRobotics/mybot_gazebo_tutorial/tree/d661a35306d4186bb33a776c47358d6848872600

## Every time you want to launch the environment (after you've followed it through once). Replace ~ with the base of your directory in each command.

source /opt/ros/melodic/setup.bash

cd ~/catkin_ws/src

catkin_init_workspace

cd ..

catkin_make

source ~/catkin_ws/devel/setup.bash

## Launching the simulation

roslaunch mybot_gazebo mybot_world.launch

## Launch the keyboard interface 

rosrun turtlesim turtle_teleop_key /turtle1/cmd_vel:=/mybot/cmd_vel

## Providing ROS commands 

rostopic pub -1 /mybot/leftWheel_effort_controller/command std_msgs/Float64 "data: 1.5"

rostopic pub -1 /mybot/rightWheel_effort_controller/command std_msgs/Float64 "data: 1.0"

See tutorial (control mode may need to be updated to pass these commands through the command line)
