#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <image_transport/image_transport.h>

namespace enc = sensor_msgs::image_encodings;
void image_callback(const sensor_msgs::ImageConstPtr& msg){
	/*
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
	*/

}
	

	
	

int main(int argc, char **argv){
	std::cout<<"TEST!/n";
	std::cout << "opencv version: " << CV_MAJOR_VERSION << std::endl;
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	image_transport::ImageTransport it(n);
	//image_transport::Subscriber sub = it.subscribe("/mybot/camera1/image_raw", 1, &image_callback);
	return 1;
}
