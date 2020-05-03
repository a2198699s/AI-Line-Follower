#include <unistd.h>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "geometry_msgs/Twist.h"

static int sensor_values[8]; 
static int count; 
static bool flag = false;

//TODO make only one callback function for all sensor inputs: see weblink
// https://answers.ros.org/question/63991/how-to-make-callback-function-called-by-several-subscriber/?answer=63998#post-id-63998
void callback(const sensor_msgs::Image::ConstPtr& msg, int index){
	sensor_values[index] = msg->data[0];
	//TODO have a better way to check for recpetion of all sensor values...
	count++;
	if(count==8){
		count=0;
		flag = true;
	}
}
void callback0(const sensor_msgs::Image::ConstPtr& msg){callback(msg, 0);}
void callback1(const sensor_msgs::Image::ConstPtr& msg){callback(msg, 1);}
void callback2(const sensor_msgs::Image::ConstPtr& msg){callback(msg, 2);}
void callback3(const sensor_msgs::Image::ConstPtr& msg){callback(msg, 3);}
void callback4(const sensor_msgs::Image::ConstPtr& msg){callback(msg, 4);}
void callback5(const sensor_msgs::Image::ConstPtr& msg){callback(msg, 5);}
void callback6(const sensor_msgs::Image::ConstPtr& msg){callback(msg, 6);}
void callback7(const sensor_msgs::Image::ConstPtr& msg){callback(msg, 7);}

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
/*===============================================================================================*/

int main(int argc, char **argv){

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

	
	ros::Publisher motors_pub = nh.advertise<geometry_msgs::Twist>("mybot/cmd_vel", 1);

	ros::Rate loop_rate(60);

	while(ros::ok()){
	
		if(flag){
			flag = false;
			geometry_msgs::Twist motors_msg;
			calculateMotorSpeeds(motors_msg);
			motors_pub.publish(motors_msg);
		}
	
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;

}
