//#include "ros/ros.h"
//#include "../include/image_subscriber_nn/nn_interface.h"
#include "../include/image_subscriber_nn/convolutional_net.h"
#include <cv_bridge/cv_bridge.h>
#include "../include/image_subscriber_nn/closed_loop_net.h"
//#include <image_transport/image_transport.h>
//#include "../../../../tiny-dnn/tiny_dnn/tiny_dnn.h"

using namespace std;

void callback0(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 0);}
void callback1(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 1);}
void callback2(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 2);}
void callback3(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 3);}
void callback4(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 4);}
void callback5(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 5);}
void callback6(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 6);}
void callback7(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 7);}

void main_callback(const sensor_msgs::Image::ConstPtr& msg){
	cv_bridge::CvImageConstPtr cv_ptr;
	try{
		std:string encode = "rgb8";
		if (sensor_msgs::image_encodings::isColor(msg->encoding))
			cv_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8);
		else
			cv_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::MONO8);
	}
	catch(cv_bridge::Exception& e){
		ROS_ERROR("cv_bridge exception: %s", e.what());
	}
	NeuralNetworkInterface::image_callback(cv_ptr, sensor_msgs::image_encodings::isColor(msg->encoding));
}

int main(int argc, char **argv){
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber sub[8];
	/*
	int layers = 4;
	int neurons[layers] = {81,40,10,1};
	int nInputs = 81;
	double learning_rate = 0.001;
	Net* neural_net = new Net(layers, neurons, nInputs);
	neural_net->initNetwork(Neuron::W_ONES, Neuron::B_NONE, Neuron::Act_Sigmoid);
	neural_net->setLearningRate(learning_rate);
	*/
	ros::Publisher motors_pub = n.advertise<geometry_msgs::Twist>("mybot/cmd_vel", 1);
	int net_choice = 1;
	NeuralNetworkInterface *chosen_nn = 0;
	switch (net_choice){
		case 1:
		{
			ClosedLoopNet *cl_nn = new ClosedLoopNet(motors_pub);
			chosen_nn = (NeuralNetworkInterface *)cl_nn;
			break;
		}
		case 2:
		{
			ConvolutionalNet *cnn = new ConvolutionalNet(motors_pub);
			chosen_nn = (NeuralNetworkInterface *)cnn;
			break;
		}
		default:
		{
			cout<<"Undefined choice of Neural Network."<<endl;
			return -1;
		}
	}
	chosen_nn->construct_nn();
	image_transport::ImageTransport it(n);
	NeuralNetworkInterface::set_current_interface(chosen_nn);
	//image_transport::Subscriber img_sub = it.subscribe("/mybot/camera1/image_raw", 1, &NeuralNetworkInterface::image_callback, ((NeuralNetworkInterface *)ncnn)); //&NeuralNetworkInterface::image_callback, interface
	//image_transport::Subscriber img_sub = it.subscribe("/mybot/camera1/image_raw", 1, boost::bind(&NeuralNetworkInterface::image_callback, _1, ncnn));
	image_transport::Subscriber img_sub = it.subscribe("/mybot/camera1/image_raw", 1, main_callback);
	
	sub[0] = n.subscribe("mybot/left_sensor4/image_raw", 1, callback0);
	sub[1] = n.subscribe("mybot/left_sensor3/image_raw", 1, callback1);
	sub[2] = n.subscribe("mybot/left_sensor2/image_raw", 1, callback2);
	sub[3] = n.subscribe("mybot/left_sensor1/image_raw", 1, callback3);
	sub[4] = n.subscribe("mybot/right_sensor1/image_raw", 1, callback4);
	sub[5] = n.subscribe("mybot/right_sensor2/image_raw", 1, callback5);
	sub[6] = n.subscribe("mybot/right_sensor3/image_raw", 1, callback6);
	sub[7] = n.subscribe("mybot/right_sensor4/image_raw", 1, callback7);
	
	ros::Rate r(60);
	ros::spin();
	return 1;
	/*
	ros::Rate loop_rate(60);
	while(ros::ok()){
		if(flag){
			flag = false;
			geometry_msgs::Twist motors_msg;
			//calculateMotorSpeeds(motors_msg);
			//motors_msg.linear.y = 100.0;
			motors_msg.linear.x = 0.2;
			motors_msg.angular.z = interface->command;
			motors_pub.publish(motors_msg);
		}
	
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
	*/
}
