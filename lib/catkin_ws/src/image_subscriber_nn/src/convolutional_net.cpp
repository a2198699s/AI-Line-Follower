#include "../include/image_subscriber_nn/convolutional_net.h"

gradient_descent opt;

void ConvolutionalNet::construct_nn(){ //TODO: enable customised size of input and number of layers
    float_t epsilon = 1.0;
    this->newcnn << conv(9, 9, 3, 1, 3) << relu() // 3 feature maps: forward, left, right
        << max_pool(7, 7, 3, 2) << relu() // in:28x28x6, 2x2pooling
        << fc(3 * 3 * 3, 12) << relu()   // in:14x14x6, out:120
        << fc(12, 1) << lrelu(epsilon);   //No support for linear activation - uses leaky relu with unit gradient instead
    assert(this->newcnn.in_data_size() == 9 * 9);
    //cout << this->newcnn.in_data_size() << endl;
    assert(this->newcnn.out_data_size() == 1);
}

float ConvolutionalNet::predict(vec_t nn_input){
	this->newcnn.predict(nn_input)[0];
}

void ConvolutionalNet::train(float error, int epochs){
	vec_t label_vec;
	vector<vec_t> input_image {{this->image_buffer[this->buff_idx]}};
	label_vec.push_back(this->output_buffer[this->buff_idx]+error);
	vector<vec_t> input_label {{label_vec}};
	size_t batch_size = 1;
	this->newcnn.fit<mse>(opt, input_image, input_label, batch_size, 3);
}

void ConvolutionalNet::update_img_buffer(vec_t img){
	this->image_buffer[this->buff_idx] = img;
}

void ConvolutionalNet::publish_motor(geometry_msgs::Twist motors_msg){
	this->motor_pub.publish(motors_msg);
}
