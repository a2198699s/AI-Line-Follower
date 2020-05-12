#include "../include/image_subscriber_nn/closed_loop_net.h"

Net *dnn = 0;

void ClosedLoopNet::construct_nn(float lr, int loss_fn, int opt, int n_layers, vector<int>activations, vector<int>neurons){
	constexpr int nLayers = 4;
	int nNeurons[nLayers] = {9*9,41,20,1};
	int* nNeuronsPtr = nNeurons;
	constexpr int nInputs = 81;
	double learningRate = 0.01;
	this->dnn = new Net(nLayers, nNeuronsPtr, nInputs);
	this->dnn->initNetwork(Neuron::W_ONES, Neuron::B_NONE, Neuron::Act_Sigmoid);
    	this->dnn->setLearningRate(learningRate);
    	this->dnn->setErrorCoeff(0,1,0,0,0,0);
}

float ClosedLoopNet::predict(vec_t nn_input){
	double *input = (double *) &nn_input[0];
	this->dnn->setInputs(input);
	this->dnn->propInputs();
	return (float)this->dnn->getOutput(0);
}	
//double *nn_image = input_img.ptr<double>(0);

void ClosedLoopNet::train(float error, int epochs){
	for (int epoch=0; epoch<epochs; epoch++){
		this->dnn->setBackwardError(error);
		this->dnn->propErrorBackward();
		this->dnn->updateWeights();
		this->dnn->saveWeights();
	}
}

void ClosedLoopNet::update_img_buffer(vec_t img){
	this->image_buffer[this->buff_idx] = img;
}

void ClosedLoopNet::publish_motor(geometry_msgs::Twist motors_msg){
	this->motor_pub.publish(motors_msg);
}
