#include <stdint.h>

#define MIN_WIDTH 1300
#define MAX_WIDTH 1700
#define PULSEWIDTH_STOP 1500

typedef enum ServoDirection_t{
	FORWARDS,
	BACKWARDS
}ServoDirection_t;

typedef enum ServoType_t{
	TYPE1, 	//forwards is max pulsewidth
	TYPE2		//forwards is min pulsewidth
}ServoType_t;

typedef struct ServoMotor_t{
	uint8_t servoPinNumber;
	ServoType_t motorType;
}ServoMotor_t;


class Servo{

	private:

		//dynamically allocated the servo pins...
		//#TODO put this in its own struct...
		ServoMotor_t* _servoPinArray;
		uint8_t _numberOfServoElements;		

		//#TODO could put direction and power in its own structure...
		int _calcServoPulsewidth(double power, ServoType_t type, ServoDirection_t direction);
		
	public:
		Servo(ServoMotor_t* servoPinArray, uint8_t numberOfElements);
		~Servo();
			
		void servo_write(int servoNumber, double power, ServoDirection_t direction);	
};
