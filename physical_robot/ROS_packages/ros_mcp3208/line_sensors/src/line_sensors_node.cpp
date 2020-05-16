#include "ros/ros.h"

#include "line_sensors/Values.h"
#include "std_msgs/String.h" //TODO my message type goes here instead
#include <sstream>


#include "Mcp3208.h"
#include "LineSensors.h"

#include <CppTimer.h>


static int count = 0;
ros::Publisher* line_sensor_data_pub;

/* Setup timer callback */
class MyTimer : public CppTimer {

	void timerEvent() {
		
		//mcp3208_ReadAllChannels(sensor_values);
		//reorderValues(sensor_values);

		//makeLine(binary_line, sensor_values);
		//printArray(binary_line);
		
		//Publish to ROS topic...
		line_sensors::Values msg;

        for(int i=0; i<8; i++){
            msg.value[i] = count++; 
        }

        //ROS_INFO("%s", msg.data.c_str());
        
        line_sensor_data_pub->publish(msg);
        
        ros::spinOnce(); //TODO what does spin do?
		
	}
};


int main(int argc, char **argv){

    //ROS initialisation...
    ros::init(argc, argv, "line_sensors");
    
    ros::NodeHandle n;

    line_sensor_data_pub = new ros::Publisher;
    
    *line_sensor_data_pub = n.advertise<line_sensors::Values>("line_sensor_data", 100);
    ros::Rate loop_rate(10);

    //mcp3208_spi_init();
    
    uint16_t sensor_values[8];
	uint16_t binary_line[8];

    //start timer...  
    MyTimer timer;  
    timer.start(1000000000); //1Hz
    
    
    while(ros::ok()){
       
        loop_rate.sleep();
    
    }
    
    delete line_sensor_data_pub;
}


