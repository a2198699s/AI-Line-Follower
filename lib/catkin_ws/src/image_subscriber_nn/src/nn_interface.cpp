
#include "../include/image_subscriber_nn/nn_interface.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;
using relu = tiny_dnn::relu_layer;

void NeuralNetworkInterface::construct_cnn() {

    //network<sequential> net;
    /*
    this->newcnn << conv(9, 9, 3, 1, 3) << relu() // 3 feature maps: forward, left, right
        << max_pool(7, 7, 3, 2) << relu() // in:28x28x6, 2x2pooling
        << fc(3 * 3 * 3, 12) << relu()   // in:14x14x6, out:120
        << fc(12, 1);      // in:120,     out:10. Using identity as it is regression problem
    */
    //assert(this->newcnn.in_data_size() == 9 * 9);
    //assert(this->newcnn.out_data_size() == 1);
    
    adagrad *opt;
    this->optimiser = opt;
    //this->newcnn = net;
}

void NeuralNetworkInterface::image_callback(const sensor_msgs::ImageConstPtr& msg){
	
	cv_bridge::CvImageConstPtr cv_ptr;
	try{
		if (enc::isColor(msg->encoding))
			cv_ptr = cv_bridge::toCvShare(msg, enc::RGB8);
		else
			cv_ptr = cv_bridge::toCvShare(msg, enc::MONO8);
	}
	catch(cv_bridge::Exception& e){
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
	
	cv::Mat input_img = cv_ptr->image;
	if (enc::isColor(msg->encoding))
		cvtColor(input_img, input_img, CV_BGR2GRAY);
	
	input_img.convertTo(input_img, CV_64F);
	imwrite("LinefollowInput.jpg", input_img);
	int rows = input_img.rows;
	int cols = input_img.cols;
	if (!input_img.isContinuous())
		input_img = input_img.clone();
	tiny_dnn::float_t *ptr = input_img.ptr<tiny_dnn::float_t>(0);
	tiny_dnn::vec_t out_vector = tiny_dnn::vec_t(ptr, ptr+rows*cols);
	//cout << "Output is: "<< this->cnn.predict(out_vector) <<endl;
	/*
	send_command(this->cnn.predict(out_vector)); 
	label = calc_label();
	this->cnn.fit<mse>(this->optimiser, out_vector, label, 1, 2);
	
	double *nn_image = input_img.ptr<double>(0);
	*/
	/*	
	this->neural_net->setInputs(nn_image);
	this->neural_net->propInputs();
	this->neural_net->setLocalError(0);
	this->neural_net->propGlobalErrorBackwardLocally();
	*/
}
	
//void send_command(tiny_dnn::vec_t command)
	
	

int main(int argc, char **argv){
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	/*
	int layers = 4;
	int neurons[layers] = {81,40,10,1};
	int nInputs = 81;
	double learning_rate = 0.001;
	Net* neural_net = new Net(layers, neurons, nInputs);
	neural_net->initNetwork(Neuron::W_ONES, Neuron::B_NONE, Neuron::Act_Sigmoid);
	neural_net->setLearningRate(learning_rate);
	*/
	NeuralNetworkInterface* interface = new NeuralNetworkInterface();//neural_net
	image_transport::ImageTransport it(n);
	image_transport::Subscriber sub = it.subscribe("/mybot/camera1/image_raw", 1, &NeuralNetworkInterface::image_callback, interface);
	ros::spin();
	return 1;
}
