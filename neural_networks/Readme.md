## Neural Networks

This folder contains all the files and packages required to run the neural networks. Several packages are also included in this directory to allow users to test the GUI as the network is operating.

There is a closed loop fully connected network and convolutional network included in this directory. The desired network can be chosen in the GUI.

## Running this package

Change to the catkin workspace in this directory and make it:

'cd neural_networks/lib/catkin_ws'

'catkin_make'

'source devel/setup.bash'

To run the neural network package, run:

'rosrun image_subscriber_nn image_subscriber_nn_node'

Make sure that the ros master is running in a separate terminal using the command 'roscore'. 


