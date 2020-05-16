#include "ros/ros.h"
#include "sumobot_motor_driver/Motors.h" 

#include "Servo.h"

#define LEFT_MOTOR_PIN_NUMBER 2
#define RIGHT_MOTOR_PIN_NUMBER 3

//pointer to class representing the servo motors
Servo *myMotors;

void set_motorsCallback(const sumobot_motor_driver::Motors::ConstPtr& msg){
    
    /*
    ROS_INFO("I heard: [%f]", msg->left_wheel_speed);
    ROS_INFO("I heard: [%f]", msg->right_wheel_speed);

    ROS_INFO("I heard: [%s]", (msg->left_wheel_direction==msg->DIRECTION_FORWARDS ? "FORWARDS" : "BACKWARDS"));
    ROS_INFO("I heard: [%s]", (msg->right_wheel_direction==msg->DIRECTION_FORWARDS ? "FORWARDS" : "BACKWARDS"));
    */

    ServoDirection_t right_servo_direction, left_servo_direction;
	
    left_servo_direction = (msg->left_wheel_direction==msg->DIRECTION_FORWARDS ? FORWARDS : BACKWARDS);
    right_servo_direction = (msg->right_wheel_direction==msg->DIRECTION_FORWARDS ? FORWARDS : BACKWARDS);
    
    myMotors->servo_write(0, msg->left_wheel_speed, left_servo_direction);
    myMotors->servo_write(1, msg->right_wheel_speed, right_servo_direction);

}


int main(int argc, char **argv){

    /* Motor type setup */
    ServoMotor_t sumoMotors[2];
    sumoMotors[0].servoPinNumber = LEFT_MOTOR_PIN_NUMBER;
    sumoMotors[0].motorType = TYPE1;
    sumoMotors[1].servoPinNumber = RIGHT_MOTOR_PIN_NUMBER;
    sumoMotors[1].motorType = TYPE2;
    	
    /* Setup of servo motors object */	
    myMotors = new Servo(sumoMotors, 2);

    /* Setup ROS */
    ros::init(argc, argv, "sumobot_motor_driver_node");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("set_motors", 100, set_motorsCallback);
    
    ros::spin();
    
    delete myMotors;
 
}
