/*
# servo_demo.c
# 2016-10-08
# Public Domain

gcc -Wall -pthread -o servo_demo servo_demo.c -lpigpio

*/

#include "Servo.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pigpio.h>


Servo::Servo(ServoMotor_t* servoPinArray, uint8_t numberOfElements){
	
	_numberOfServoElements = numberOfElements;
	_servoPinArray = new ServoMotor_t[_numberOfServoElements];	
	
	for(int i=0; i<_numberOfServoElements; i++){
		_servoPinArray[i] = servoPinArray[i];
	}	

  gpioInitialise();
	//gpioSetSignalFunc(SIGINT, stop);
	
	for(int i=0; i<_numberOfServoElements; i++){
		gpioServo(_servoPinArray[i].servoPinNumber, 0);
	}

}

Servo::~Servo(){

	for(int i=0; i<_numberOfServoElements; i++){
		gpioServo(_servoPinArray[i].servoPinNumber, 0);
	}
	gpioTerminate();	

	delete[] _servoPinArray;

}

int Servo::_calcServoPulsewidth(double power, ServoType_t type, ServoDirection_t direction){
	
	int pulsewidth;

	//#TODO check if motor types are correct for the sumobot?
	switch(type){
		case TYPE1:
			if(direction==FORWARDS){
				pulsewidth = ((MAX_WIDTH - PULSEWIDTH_STOP) * power) + PULSEWIDTH_STOP;
			}
			else{ //BACKWARDS
				pulsewidth = ((MIN_WIDTH - PULSEWIDTH_STOP) * power) + PULSEWIDTH_STOP;
			}
		break;

		case TYPE2:
			if(direction==FORWARDS){
				pulsewidth = ((MIN_WIDTH - PULSEWIDTH_STOP) * power) + PULSEWIDTH_STOP;
			}
			else{ //BACKWARDS
				pulsewidth = ((MAX_WIDTH - PULSEWIDTH_STOP) * power) + PULSEWIDTH_STOP;
			}
		break;

		default:
		break;
	}

	return pulsewidth;
}

void Servo::servo_write(int servoNumber, double power, ServoDirection_t direction){
	
	int pulsewidth = _calcServoPulsewidth(power, 
																				_servoPinArray[servoNumber].motorType,
																				direction);

	gpioServo(_servoPinArray[servoNumber].servoPinNumber, pulsewidth);

}
