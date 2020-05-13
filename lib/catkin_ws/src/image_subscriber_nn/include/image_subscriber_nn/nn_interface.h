#ifndef NN_INTERFACE
#define NN_INTERFACE
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <image_transport/image_transport.h>
#include "../../../../../tiny-dnn/tiny_dnn/tiny_dnn.h"
#include <typeinfo>
#include <stdlib.h>
#include <unistd.h>
#include "geometry_msgs/Twist.h"
#include <chrono>

#define BUFFER_LENGTH 14

using namespace tiny_dnn;
using namespace std;


class NeuralNetworkInterface{
public:
	
	static void image_callback(cv_bridge::CvImageConstPtr cv_ptr, bool is_colour);
	static void sensor_callback(const sensor_msgs::Image::ConstPtr& msg, int index);
	float command;
	virtual void construct_nn(float lr, int loss_fn, int opt, int n_layers, vector<int>activations, vector<int>neurons) = 0;
	virtual float predict(vec_t input) = 0;
	virtual void train(float error, int epochs=1) = 0;
	virtual void update_img_buffer(vec_t img) = 0;
	virtual void publish_motor(geometry_msgs::Twist motors_msg) = 0;
	virtual void publish_error(float error) = 0;
	virtual void publish_command(float command) = 0;
	static void set_current_interface(NeuralNetworkInterface* interface);
	static NeuralNetworkInterface *interface;


protected:
	void *optimiser;
	static int count; 
	//static bool flag;
	static float calc_error();
	void train_cycle(float command, vec_t nn_input);
	void send_command(float command, float speed=0.2);
	int buff_idx=0;
	int buff_len=BUFFER_LENGTH;
	float output_buffer[BUFFER_LENGTH];
	bool start_learning=false;
	
	
	//static int sensor_weights[8];
};
#endif
