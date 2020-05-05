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
#include <stdlib.h>
#include <unistd.h>
#include "geometry_msgs/Twist.h"
#include <chrono>


using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;
using relu = tiny_dnn::relu_layer;
using lrelu = tiny_dnn::leaky_relu_layer;
namespace enc = sensor_msgs::image_encodings;

class NeuralNetworkInterface{
public:
	NeuralNetworkInterface(ros::Publisher &motor_pub){//Net* neural_net
		//this->neural_net = neural_net;
		this->newcnn = network<sequential>("CBCNN");
		this->motor_pub = motor_pub;
		//cout<<typeid(this->newcnn).name() << endl;
	}
	void image_callback(const sensor_msgs::ImageConstPtr& msg);
	static void sensor_callback(const sensor_msgs::Image::ConstPtr& msg, int index);
	void construct_cnn();
	float command;


private:
	Net* neural_net;
	tiny_dnn::network<sequential> newcnn;
	void *optimiser;
	static int count; 
	//static bool flag;
	static float calc_error();
	ros::Publisher motor_pub;
	void send_command(float command, float speed=0.2);
	
	//static int sensor_weights[8];
};
