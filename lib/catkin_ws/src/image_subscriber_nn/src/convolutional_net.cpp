#include "../include/image_subscriber_nn/convolutional_net.h"

gradient_descent optim;
void ConvolutionalNet::construct_nn(float lr, int loss_fn, int opt, int n_layers, vector<int>activations, vector<int>neurons){ 
    this->newcnn << conv(9, 9, 3, 1, 3)
    		 << max_pool(7, 7, 3, 2);

    this->newcnn << fc(3 * 3 * 3, neurons[0]);
    this->add_activation_fn(activations[0]);
    for( int layer=1; layer<n_layers; layer++){
        this->newcnn << fc(neurons[layer-1], neurons[layer]);
    	this->add_activation_fn(activations[layer]);
    }
    this->loss_fn = loss_fn;
    optim.alpha = lr;

    assert(this->newcnn.in_data_size() == 9 * 9);
    assert(this->newcnn.out_data_size() == 1);
}


void ConvolutionalNet::add_activation_fn(int choice){
	switch (choice){
		case 0:
			this->newcnn << tanh_act();
			break;
		case 1:
			this->newcnn << asinh_act();
			break;
		case 2:
			this->newcnn << sigmoid();
			break;
		case 3:
			this->newcnn << relu();
			break;
		case 4:
		{
			float_t epsilon = 0.01;
			this->newcnn << lrelu(epsilon); 
			break;
		}
		case 5:
			this->newcnn << softmax();
			break;
		case 6:
		{
			float_t epsilon = 1.0; //No support for linear activation - uses leaky relu with unit gradient instead
			this->newcnn << lrelu(epsilon); 
			break;
		}
		default:
			cout<<"Undefined choice of activation function: "<<choice<<endl;
			break;
	}
}

void ConvolutionalNet::train_cnn(vector<vec_t> input_image, vector<vec_t> input_label){
	size_t batch_size = 1;
	switch (this->loss_fn){
		case 0:
			this->newcnn.fit<cross_entropy>(optim, input_image, input_label, batch_size, 3);
			break;
		case 1:
			this->newcnn.fit<mse>(optim, input_image, input_label, batch_size, 3);
			break;
		default:
			cout<<"Undefined choice of loss function: "<<this->loss_fn<<endl;
			break;
	}
		
}

void ConvolutionalNet::publish_error(float cl_error){
	std_msgs::Float64 msg;
	msg.data = cl_error;
	this->error_pub.publish(msg);
}

void ConvolutionalNet::publish_command(float output){
	std_msgs::Float64 msg;
	msg.data = output;
	this->out_pub.publish(msg);
}


float ConvolutionalNet::predict(vec_t nn_input){
	this->newcnn.predict(nn_input)[0];
}

int countRuns = 0;
void ConvolutionalNet::train(float error, int epochs){
	vec_t label_vec;
	vector<vec_t> input_image {{this->image_buffer[this->buff_idx]}};
	label_vec.push_back((this->output_buffer[this->buff_idx]+error)/1.5);
	vector<vec_t> input_label {{label_vec}};
	this->train_cnn(input_image, input_label);
	image<uint8_t> kernel = this->newcnn.at<conv>(0).weight_to_image();
	vec_t vec_kernel = kernel.to_vec(); 
	vector<uint8_t> msg_kernel;
	for (int i=0; i<vec_kernel.size(); i++){
		msg_kernel.push_back(vec_kernel[i]);
	}
	sensor_msgs::Image msg;
        msg.header.seq = countRuns;
        msg.header.frame_id = "conv_kernels";
        msg.height = 5;
        msg.width = 13;
        msg.encoding = "mono8";
        msg.is_bigendian = 0;
        msg.step = 13;
	msg.data = msg_kernel;
	this->kernel_pub.publish(msg);
}

void ConvolutionalNet::update_img_buffer(vec_t img){
	this->image_buffer[this->buff_idx] = img;
}

void ConvolutionalNet::publish_motor(geometry_msgs::Twist motors_msg){
	this->motor_pub.publish(motors_msg);
}
