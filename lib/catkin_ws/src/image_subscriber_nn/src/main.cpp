
#include "../include/image_subscriber_nn/convolutional_net.h"
#include <cv_bridge/cv_bridge.h>
#include "../include/image_subscriber_nn/closed_loop_net.h"
#include "rqt_neural_net_control/GetNeuralNetConfig.h"
#include "rqt_line_sensor_control/GetSensorsWeights.h"

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
	//cv_bridge image processing must be done in main.cpp to avoid c++11 clashes
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
	ros::ServiceClient client = n.serviceClient<rqt_neural_net_control::GetNeuralNetConfig>("neural_net_config");
	rqt_neural_net_control::GetNeuralNetConfig srv;
	float lr = 0.01;
	int loss_fn = 0;
	int opt = 0;
	bool conv = 1;
	int n_layers = 2;
	double in_multiplier = 1.0;
	double out_multiplier = 1.0;
	double err_multiplier = 1.0;
	vector<int> activations;
	vector<int> neurons;
	if(client.call(srv)){
		lr = srv.response.learning_rate;
		loss_fn = srv.response.loss_function;
		opt = srv.response.optimiser;
		conv = srv.response.convolutional_net_enabled;
		n_layers = srv.response.number_of_layers;
		in_multiplier = srv.response.input_multiplier;
		out_multiplier = srv.response.output_multiplier;
		err_multiplier = srv.response.closed_loop_error_multiplier;
		
		for(int i=0; i<srv.response.number_of_layers; i++){
			 activations.push_back(srv.response.layer_activations[i]);
			 neurons.push_back(srv.response.layer_neuron_count[i]);
		}
	}
	else{
		activations = {3,6};
		neurons = {12,1};
	}
	rqt_line_sensor_control::GetSensorsWeights sensor_srv;
	ros::ServiceClient sensor_client = n.serviceClient<rqt_line_sensor_control::GetSensorsWeights>("get_sensor_weights");
	if (sensor_client.call(sensor_srv)){
		NeuralNetworkInterface::update_sensor_weights(sensor_srv.response.sensor_weight);
	}
	ros::Publisher motors_pub = n.advertise<geometry_msgs::Twist>("mybot/cmd_vel", 1);
	ros::Publisher out_pub = n.advertise<std_msgs::Float64>("neural_net/output_node", 1);
	ros::Publisher error_pub = n.advertise<std_msgs::Float64>("neural_net/closed_loop_error", 1);
	NeuralNetworkInterface *chosen_nn = 0;
	switch (conv){
		case 0:
		{
			ClosedLoopNet *cl_nn = new ClosedLoopNet(motors_pub, out_pub, error_pub);
			cl_nn->set_multipliers(in_multiplier, out_multiplier, err_multiplier);
			cout << "CLOSED LOOP NET CHOSEN"<<endl;
			chosen_nn = (NeuralNetworkInterface *)cl_nn;
			break;
		}
		case 1:
		{
			ros::Publisher kernel_pub = n.advertise<sensor_msgs::Image>("neural_net/kernel_weights", 1);
			ConvolutionalNet *cnn = new ConvolutionalNet(motors_pub, out_pub, error_pub,kernel_pub);
			cout << "CONVOLUTIONAL NET CHOSEN"<<endl;
			chosen_nn = (NeuralNetworkInterface *)cnn;
			break;
		}
		default:
		{
			cout<<"Undefined choice of Neural Network."<<endl;
			return -1;
		}
	}
	chosen_nn->construct_nn(lr, loss_fn, opt, n_layers, activations, neurons);
	image_transport::ImageTransport it(n);
	NeuralNetworkInterface::set_current_interface(chosen_nn);
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
}
