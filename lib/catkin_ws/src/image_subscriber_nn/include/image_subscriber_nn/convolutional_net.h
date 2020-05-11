#ifndef CONV
#define CONV
#include "nn_interface.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;
using relu = tiny_dnn::relu_layer;
using lrelu = tiny_dnn::leaky_relu_layer;


class ConvolutionalNet: public NeuralNetworkInterface{
	public:
		ConvolutionalNet(ros::Publisher &motor_pub){
			this->newcnn = network<sequential>("CBCNN");
			this->motor_pub = motor_pub;
		}

		void construct_nn();
		float predict(vec_t input);
		void train(float error, int epochs=1);
		void update_img_buffer(vec_t img);
		void publish_motor(geometry_msgs::Twist motors_msg);
	
	protected:
		tiny_dnn::network<sequential> newcnn;
		ros::Publisher motor_pub;
		vec_t image_buffer[3];
};

#endif
