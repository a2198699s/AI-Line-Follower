#ifndef CLOSEDL
#define CLOSEDL
#include "nn_interface.h"
#include "../../../../../CLDL/include/cldl/Net.h"
#include "../../../../../CLDL/include/cldl/Neuron.h"
#include <std_msgs/Float64.h>


class ClosedLoopNet: public NeuralNetworkInterface{
	public:
		ClosedLoopNet(ros::Publisher &motor_pub,ros::Publisher &out_pub,ros::Publisher &error_pub){
			this->motor_pub = motor_pub;
			this->out_pub = out_pub;
			this->error_pub = error_pub;
		}
		void construct_nn(float lr, int loss_fn, int opt, int n_layers, vector<int>activations, vector<int>neurons);
		float predict(vec_t nn_input);
		void train(float error, int epochs);
		void update_img_buffer(vec_t img);
		void publish_motor(geometry_msgs::Twist motors_msg);
		void publish_error(float error);
		void publish_command(float command);
		void set_multipliers(double in_multiplier, double out_multiplier, double err_multiplier);
		Net *dnn;

	protected:
		double in_multiplier;
		double out_multiplier;
		double err_multiplier;
		ros::Publisher motor_pub;
		ros::Publisher out_pub;
		ros::Publisher error_pub;
		vec_t image_buffer[BUFFER_LENGTH];
};

#endif
