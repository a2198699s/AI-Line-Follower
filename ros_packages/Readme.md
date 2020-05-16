# ROS Packages

This folder contains misc. ROS packages used for the project.

## Contents

* __line_react_control:__ this package is used to provide line following capability to the Gazebo simulation. It takes the line sensor values published by Gazebo as an input and publishes a motor control message

* __enki_line_react_control:__ this package is used to provide line following capability to the Enki simulation. It takes the line sensor values published by Gazebo as an input and publishes a motor control message

## How to use

Copy the package you want to use to a catkin workspace (catkin_ws/src)
```
catkin_make
source devel/setup.bash
```

To run, ensure roscore is running and the desired target simulation.
```
rosrun <package_name> <exe_name>
```

