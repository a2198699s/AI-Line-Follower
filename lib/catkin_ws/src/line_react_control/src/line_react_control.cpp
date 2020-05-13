#include <unistd.h>

#include <chrono>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "geometry_msgs/Twist.h"

static int sensor_values[8]; 
static int count; 
static bool flag = false;

class MyClass{

public:
  static void callback(const sensor_msgs::Image::ConstPtr& msg, int index);

};


void MyClass::callback(const sensor_msgs::Image::ConstPtr& msg, int index){
	sensor_values[index] = msg->data[0];
	count++;
	if(count==8){
		count=0;
		flag = true;
	}

}
void callback0(const sensor_msgs::Image::ConstPtr& msg){MyClass::callback(msg, 0);}
void callback1(const sensor_msgs::Image::ConstPtr& msg){MyClass::callback(msg, 1);}
void callback2(const sensor_msgs::Image::ConstPtr& msg){MyClass::callback(msg, 2);}
void callback3(const sensor_msgs::Image::ConstPtr& msg){MyClass::callback(msg, 3);}
void callback4(const sensor_msgs::Image::ConstPtr& msg){MyClass::callback(msg, 4);}
void callback5(const sensor_msgs::Image::ConstPtr& msg){MyClass::callback(msg, 5);}
void callback6(const sensor_msgs::Image::ConstPtr& msg){MyClass::callback(msg, 6);}
void callback7(const sensor_msgs::Image::ConstPtr& msg){MyClass::callback(msg, 7);}

void calculateMotorSpeeds(geometry_msgs::Twist& msg){
	
	int index = 0;
	int min = sensor_values[0];
	for(int i=1; i<8; i++){
		if(sensor_values[i]<min){
			index = i;
			min = sensor_values[i];
		}
	}
	
	//now we have the index of the smallest...
	//TODO convert this to a motor speed...
	/*msg.linear.x = 10;
		msg.linear.y = 0;
		msg.linear.z = 0;
		
		msg.angular.x = 10;
		msg.angular.y = 0;
		msg.angular.z = 0;
	*/
}

auto cbtime = std::chrono::high_resolution_clock::now();
bool started = false;
void callback_img_test(const sensor_msgs::ImageConstPtr& msg){
	auto finish = std::chrono::high_resolution_clock::now();
	if (started){
		std::chrono::duration<double> elapsed = finish -cbtime;
		std::cout << "Time: " << elapsed.count() << std::endl;
	}else{
		started = true;
	}
	cbtime = finish;
}

/*===============================================================================================*/

int main(int argc, char **argv){

  //MyClass Mikkel;

	ros::init(argc, argv, "line_react_control_node");
	ros::NodeHandle nh;
	ros::Subscriber sub[8];
	
	sub[0] = nh.subscribe("mybot/left_sensor4/image_raw", 1, callback0);
	sub[1] = nh.subscribe("mybot/left_sensor3/image_raw", 1, callback1);
	sub[2] = nh.subscribe("mybot/left_sensor2/image_raw", 1, callback2);
	sub[3] = nh.subscribe("mybot/left_sensor1/image_raw", 1, callback3);
	sub[4] = nh.subscribe("mybot/right_sensor1/image_raw", 1, callback4);
	sub[5] = nh.subscribe("mybot/right_sensor2/image_raw", 1, callback5);
	sub[6] = nh.subscribe("mybot/right_sensor3/image_raw", 1, callback6);
	sub[7] = nh.subscribe("mybot/right_sensor4/image_raw", 1, callback7);

	ros::Subscriber mikkel = nh.subscribe("mybot/camera1/image_raw", 1, &callback_img_test);	

	ros::Publisher motors_pub = nh.advertise<geometry_msgs::Twist>("mybot/cmd_vel", 1);

	ros::Rate loop_rate(60);

	ros::spin();

	/*while(ros::ok()){
	
		if(flag){
			flag = false;
			geometry_msgs::Twist motors_msg;
			calculateMotorSpeeds(motors_msg);
			motors_pub.publish(motors_msg);
		}
	
		ros::spinOnce();
		loop_rate.sleep();
	}*/

	return 0;

}
