
#include "../include/image_subscriber_nn/nn_interface.h"

void NeuralNetworkInterface::image_callback(const sensor_msgs::ImageConstPtr& msg){
	
	cv_bridge::CvImageConstPtr cv_ptr;
	try{
		if (enc::isColor(msg->encoding))
			cv_ptr = cv_bridge::toCvShare(msg, enc::BGR8);
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
	int rows = input_img.rows;
	int cols = input_img.cols;
	cout<< "Pic has "<<rows<<" rows and "<<cols<<" cols."<<endl;

	if (!input_img.isContinuous())
		input_img = input_img.clone();
	
	double *nn_image = input_img.ptr<double>(0);
		
	//this->neural_net->setInputs(nn_image);
}
	

	
	

int main(int argc, char **argv){
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	int layers = 3;
	int neurons[layers] = {10,5,1};
	int nInputs = 10;
	Net* neural_net = new Net(layers, neurons, nInputs);
	NeuralNetworkInterface* interface = new NeuralNetworkInterface(neural_net);
	image_transport::ImageTransport it(n);
	image_transport::Subscriber sub = it.subscribe("/mybot/camera1/image_raw", 1, &NeuralNetworkInterface::image_callback, interface);
	ros::spin();
	return 1;
}
