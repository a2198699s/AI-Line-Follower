#ifndef CLOSEDL
#define CLOSEDL
#include "nn_interface.h"
#include "../../../../../CLDL/include/cldl/Net.h"
#include "../../../../../CLDL/include/cldl/Neuron.h"


class ClosedLoopNet: public NeuralNetworkInterface{
	public:
		ClosedLoopNet(ros::Publisher &motor_pub){
			this->motor_pub = motor_pub;
		}
		void construct_nn(float lr, int loss_fn, int opt, int n_layers, vector<int>activations, vector<int>neurons);
		float predict(vec_t nn_input);
		void train(float error, int epochs);
		void update_img_buffer(vec_t img);
		void publish_motor(geometry_msgs::Twist motors_msg);
		Net *dnn;

	private:
		
		ros::Publisher motor_pub;
		vec_t image_buffer[BUFFER_LENGTH];
};

#endif
