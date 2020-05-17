# Simulation Setup Notes

Robot construction modified from this [Tutorial](https://www.generationrobots.com/blog/en/robotic-simulation-scenarios-with-gazebo-and-ros/)

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
