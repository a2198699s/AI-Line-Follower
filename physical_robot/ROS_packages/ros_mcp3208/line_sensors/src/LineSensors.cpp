#include "LineSensors.h"

#include <iostream>

void reorderValues(uint16_t* sensor_values){

    /* Make copy of sensor values */
	uint16_t temp[8];
	for(int i=0;i<8;i++){
		temp[i] = sensor_values[i];
	}

    /* Re-assign in correct order */
	sensor_values[0] = temp[3];
	sensor_values[1] = temp[2];
	sensor_values[2] = temp[1];
	sensor_values[3] = temp[0];
	sensor_values[4] = temp[7];
	sensor_values[5] = temp[6];
	sensor_values[6] = temp[5];
	sensor_values[7] = temp[4];

}


void printArray(uint16_t* array_values){

    std::cout << "ARRRAY VALUES: ";
	for(int i=0;i<8;i++){
		std::cout << array_values[i] << " ";
	}
	std::cout << std::endl << std::endl;

}

uint16_t getArrayAverage(uint16_t* array_values){

	long sum = 0;
	for(int i=0; i<8;i++){
		sum += array_values[i];
	}
	return sum/8;

}

void makeBinaryLine(uint16_t* bin_line, uint16_t* sensor_values){

    uint16_t average = getArrayAverage(sensor_values);    
    
	for(int i=0; i<8;i++){
		if((sensor_values[i]) > (average * BINARY_THRESHOLD)){
			bin_line[i] = 1;		
		}
		else{
			bin_line[i] = 0;
		}
	}
    

}
