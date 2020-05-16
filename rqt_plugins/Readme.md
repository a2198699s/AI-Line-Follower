# Custom rqt Plugins
This directory contains ROS packages which provide custom GUI plugins for rqt (a ROS based GUI framework). 


## Package Descriptions

* __rqt_line_sensor_control:__ this package provides line sensor configuration options which are requested by the neural network module when it is launched 

* __rqt_line_sensor_view:__ this package provides a real-time display of the line sensor array values published by the robot module

* __rqt_neural_net_control:__ this package provides neural network configuration options which are requested by the neural network module when it is launched

* __rqt_neural_network_diagnostics:__ this package provides a real-time display of outputs from the neural network module


## How to use

Copy the package(s) you want to use to a catkin workspace (catkin_ws).
From the catkin_ws run:
```
catkin_make
```
This should build the packages.
It is good practice to source the workspace after this:
```
source devel/setup.bash
```

To use the plugins, make sure roscore is running.
Then start rqt:
```
rqt --force-discover
```
The plugins should be found in the Design Special Topic 5 folder in the plugins dropdown.

## Instructions for making your own, custom, rqt plugin

* Setup a Catkin Workspace
Catkin is the build system used with ROS. If you don't already have one, just follow the instructions on the ROS wiki http://wiki.ros.org/ROS/Tutorials to set it up

* Create an empty plugin

Clone this repository https://github.com/leggedrobotics/catkin_create_rqt
```
git clone https://github.com/leggedrobotics/catkin_create_rqt
```
From this repository you can run a script to create a blank rqt plugin.
The command line call takes several arguments, and these are the main ones you'll want to change...
  
* dependencies : list the dependencies you need, the main ones you'll need are the ROS message types like *std_msgs* or *sensor_msgs*. If you don't know what you need they can be added later anyway... 
  
* -p : make this the path to your catkin workspace src folder
  
* -c : change the name of the main QT class
  
* -n : change the name of the namespace used for that class
  
* -f : change the names of the files used for the QT class
 
* -a and -e : can be changed later

An example call:
```
./catkin_create_rqt rqt_line_sensor_viewer std_msgs -p ~/catkin_ws/src -c LineSensorViewer -n linesensorviewer -f LineSensorViewer
```
NB. rqt_line_sensor_viewer is the name of the package to create

* Adapt package.xml

Here you can add your email and licence etc. BSD licence is most commonly used for ROS

* Adapt plugin.xml

Here you change stuff to do with your plugin. The first group label is the folder that it is kept in in rqt.

The second group label is the name of your plugin that appears on rqt. You can change the icon, some of which can be found at https://specifications.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html

* Add all your QT and ROS stuff

* When finished change directory to your catkin workspace

Then, as described before
```
catkin_make 
```
```
source devel/setup.bash
```
With roscore running 
```
rqt --force-discover
```
