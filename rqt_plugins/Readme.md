## Instructions for making your own rqt plugin

* Setup a Catkin Workspace
Catkin is the build system for ROS. Just follow the instructions on the ROS wiki http://wiki.ros.org/ROS/Tutorials to set it up

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
  my call looked a bit like this
  ```
  ./catkin_create_rqt rqt_line_sensor_viewer std_msgs -p ~/catkin_ws/src -c LineSensorViewer -n linesensorviewer -f LineSensorViewer
  ```
  NB. rqt_line_sensor_viewer is the name of the package I want to create

* Adapt package.xml

Here you can add your email and licence and stuff. I think BSD licence is mostly used for ROS

* Adapt plugin.xml

Here you change stuff to do with your plugin. The first group label is the folder that it is kept in in rqt, I called mine Design Special Project 5.

The second group label is the name of your plugin that appears on rqt. You can change the icon, some of which can be found at https://specifications.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html

* Add all your QT and ROS stuff

* When finished change directory to your catkin workspace

Then...
```
catkin_make install
```

then to see your plugin just call rqt. Sometimes the plugin doesn't show first time so use 
```
rqt --force-discover
```

