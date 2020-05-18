#include "../include/image_subscriber_nn/closed_loop_net.h"

Net *dnn = 0;

void ClosedLoopNet::construct_nn(float lr, int loss_fn, int opt, int n_layers, vector<int>activations, vector<int>neurons){
	int nNeurons[n_layers];
	nNeurons[0] = 9*9;
	for (int i=1; i<n_layers; i++){
		nNeurons[i] = neurons[i];
	}
	int* nNeuronsPtr = nNeurons;
	constexpr int nInputs = 81;
	double learningRate = lr;
	this->dnn = new Net(n_layers, nNeuronsPtr, nInputs);
	this->dnn->initNetwork(Neuron::W_ONES, Neuron::B_NONE, Neuron::Act_Sigmoid);
    	this->dnn->setLearningRate(learningRate);
    	this->dnn->setErrorCoeff(0,1,0,0,0,0);
}

void ClosedLoopNet::set_multipliers(double in_multiplier, double out_multiplier, double err_multiplier){
	this->in_multiplier = in_multiplier;
	this->out_multiplier = out_multiplier;
	this->err_multiplier = err_multiplier;
}

float ClosedLoopNet::predict(vec_t nn_input){
	double *input = (double *) &nn_input[0];
	this->dnn->setInputs(input);
	this->dnn->propInputs();
	double out = this->out_multiplier * this->dnn->getOutput(0);
	return (float)out;
}	

void ClosedLoopNet::train(float error, int epochs){
	float m_error = (float)(this->err_multiplier) * error;
	for (int epoch=0; epoch<epochs; epoch++){
		this->dnn->setBackwardError(m_error);
		this->dnn->propErrorBackward();
		this->dnn->updateWeights();
		//this->dnn->saveWeights();
	}
}

void ClosedLoopNet::publish_error(float cl_error){
	std_msgs::Float64 msg;
	msg.data = cl_error;
	this->error_pub.publish(msg);
}

void ClosedLoopNet::publish_command(float output){
	std_msgs::Float64 msg;
	msg.data = output;
	this->out_pub.publish(msg);
}

void ClosedLoopNet::update_img_buffer(vec_t img){
	this->image_buffer[this->buff_idx] = img;
}

void ClosedLoopNet::publish_motor(geometry_msgs::Twist motors_msg){
	this->motor_pub.publish(motors_msg);
}
