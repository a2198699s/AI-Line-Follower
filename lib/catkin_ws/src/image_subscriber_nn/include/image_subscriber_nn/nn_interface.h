#include "ros/ros.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <image_transport/image_transport.h>
#include "../../../../../include/clbp/Net.h"
#include "../../../../../include/clbp/Neuron.h"
#include "../../../../../tiny-dnn/tiny_dnn/tiny_dnn.h"
#include <typeinfo>

namespace enc = sensor_msgs::image_encodings;

class NeuralNetworkInterface{
public:
	NeuralNetworkInterface(){//Net* neural_net
		//this->neural_net = neural_net;
		this->newcnn = &tiny_dnn::network<sequential>;
		cout<<typeid(this->newcnn).name() << endl;
	}
	void image_callback(const sensor_msgs::ImageConstPtr& msg);


private:
	Net* neural_net;
	tiny_dnn::network<sequential> *newcnn;
	void construct_cnn();
	void *optimiser;
};
