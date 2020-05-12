#ifndef CONV
#define CONV
#include "nn_interface.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;
using relu = tiny_dnn::relu_layer;
using lrelu = tiny_dnn::leaky_relu_layer;
using tanh_act = tiny_dnn::tanh_layer;
using asinh_act = tiny_dnn::asinh_layer;
using sigmoid = tiny_dnn::sigmoid_layer;
using softmax = tiny_dnn::softmax_layer;


class ConvolutionalNet: public NeuralNetworkInterface{
	public:
		ConvolutionalNet(ros::Publisher &motor_pub){
			this->newcnn = network<sequential>("CBCNN");
			this->motor_pub = motor_pub;
		}

		void construct_nn(float lr, int loss_fn, int opt, int n_layers, vector<int>activations, vector<int>neurons);
		float predict(vec_t input);
		void train(float error, int epochs=1);
		void update_img_buffer(vec_t img);
		void publish_motor(geometry_msgs::Twist motors_msg);
	
	protected:
		tiny_dnn::network<sequential> newcnn;
		ros::Publisher motor_pub;
		vec_t image_buffer[BUFFER_LENGTH];
		int loss_fn;
		void add_activation_fn(int choice);
		void set_loss_fn(int choice);
		void set_optimiser(int choice);
		void train_cnn(vector<vec_t> input_image, vector<vec_t> input_label);
};

#endif
