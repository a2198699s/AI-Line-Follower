## Work Inspiration 

This project involves the development of an AI line following robot.

The robot, which is constructed using a Raspberry Pi as the controller, uses deep learning to predict required movements in order to follow a line.

The error signal for the neural network is generated using a set of sensors on the bottom of the robot. During the learning phase, the robot uses these sensors and a reflex based control system to follow the line. The neural network uses the images input using a camera mounted on the front to predict the required movements to reduce the error signal. It uses a closed-loop back propagation system to perform this.

This project involves investigation into potential improvements to the current system; for example constant error propagation, and convelutional input filtering. The current system is described in: https://arxiv.org/pdf/2001.02970.pdf

---
## Repository Description

This repository provides a ROS (Robot Operating System) based framework for development and testing of neural network implementations with a line following robot. The line following robot can be realised as either a simulation or as a physical robot.

---

## Contents

* __rqt_plugins:__ this directory contains the custom rqt GUI plugins used for the project

* __ros_packages:__ this directory contains some misc. ROS packages useful for the project

* __physical_robot:__ this directory contains work related with the development of the physical robot for the project

* __simulators:__ this directory contains simulator packages used in the framework

* __neural_networks:__ this directory contains the neural network implementations used in the project

* __interface_specifications:__ this directory contains specifications for module interfaces for the framework


## How to use

Instructions for using each section of the framework can be found in the respective folder.

In general however, ROS is a common requirement for all modules. The ROS distribution used for this project was Melodic ROS.

Instructions for getting started with ROS can be found on the [ROS Wiki](http://wiki.ros.org/ROS/Tutorials).

__This repository is also dependent on submodules so when cloning use:__
```
git clone https://github.com/a2198699s/AI-Line-Follower --recurse-submodules
```
