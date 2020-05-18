# Enki (QT5)

a fast 2D robot simulator using the QT5 build system.

© 1999-2017 Stéphane Magnenat and others ([full list](AUTHORS))

© 2017 Bernd Porr <mail@berndporr.me.uk>


## License

[GPL 2.0](LICENSE).

# Description
This project provides an additional ROS based package in the examples directory. This gives an example for using the enki simulator with the ROS framework used in [AI-Line-Follower](https://github.com/a2198699s/AI-Line-Follower).

# Use with ROS

First the enki library needs to be built:
```
cd enkiSimulator
cd enki
qmake
make
```

Then we want to build the ROS package
```
cd ..
cd examples/ros_example/catkin_ws
catkin_make
```
NOTE: you might have to empty the catkin_ws/devel and catkin_ws/build folders due to saved user specific cache stuff

To run:
source the workspace
```
source devel/setup.bash
```
and run with
```
rosrun enki_ros_pck robot
```
