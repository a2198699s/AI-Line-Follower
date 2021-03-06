# Simulation Setup Notes

Robot construction modified from this [Tutorial](https://www.generationrobots.com/blog/en/robotic-simulation-scenarios-with-gazebo-and-ros/)

Note: this tutorial is for an ROS Hydro and this repo uses ROS Melodic and so some changes have been made. Additionally, when installing packages (e.g. controller drivers) ensure the melodic versions are installed. The Github for this tutorial can be found at: https://github.com/HumaRobotics/mybot_gazebo_tutorial/tree/d661a35306d4186bb33a776c47358d6848872600

## Package Descriptions
The Gazebo simulation environment uses a number of packages.

### mybot_control
This package sets up the robot actuators (joint effort controllers) and links to the actuator topics to allow the robot to be controlled.

### mybot_description
This package contains the urdf description of the robot which defines the robot (including it's sensors and sensor types as well as the dimensions and placement). 

### mybot_gazebo
This package is used to launch the simulation. It defines the line-track simulation environment (which uses an [image](https://github.com/a2198699s/AI-Line-Follower/blob/master/simulators/Gazebo/catkin_ws/src/MOVE_ME/materials/textures/MyImage.png) which needs to be moved to the standard environment folder as described in this [folder](https://github.com/a2198699s/AI-Line-Follower/tree/master/simulators/Gazebo/catkin_ws/src/MOVE_ME). It contains a configuration file for Rviz to allow for the robot to be visualised.


## Every time you want to launch the environment (after you've followed it through once). Replace ~ with the base of your directory in each command.

source /opt/ros/melodic/setup.bash

cd ~/catkin_ws/src

catkin_init_workspace

cd ..

catkin_make

source ~/catkin_ws/devel/setup.bash

## Launching the simulation

roslaunch mybot_gazebo mybot_world.launch
