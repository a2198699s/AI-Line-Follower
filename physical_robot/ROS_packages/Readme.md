## ROS Packages

This folder contains ROS package templates for using with the physical robot

## Contents

* __ros_mcp3208:__ package for obtaining the sensor values from the line sensor PCB ADC. This package then publishes the values on a ROS topic

* __ros_sumobot_motors_driver:__ package for controlling the Sumobot continuous rotation servo motors. This package subscribes to a ROS motor topic and converts the command to motor commands.

Disclaimer: these packages have not yet been tested or made compatible with the ROS based framework for the project. They are to act as templates for continued work.

## How to use

Copy the package to a catkin_ws/src directory on the Raspberry Pi.
In the catkin_ws
```
catkin_make
```
```
source devel/setup.bash
```

Use the *rosrun* command to run the package, ensuring *roscore* is running.

