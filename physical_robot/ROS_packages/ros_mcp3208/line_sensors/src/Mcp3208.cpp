#include "Mcp3208.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern "C"{
#include <wiringPi.h>
#include <wiringPiSPI.h>
}

#include <math.h>

#define ADC_RESOLUTION_BITS 12
#define ADC_LEVELS 4096

void mcp3208_spi_init(){

  wiringPiSetup();
  if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
    printf("wiringPiSPISetup failed in SPI %d.\n", SPI_CHANNEL);
    exit(EXIT_FAILURE);
  }
}

//! Arduino like Analog read function
/*!
  \param adc_pin ADC pin number (0 - 7)
  \return analog bit (0 - 4095)
*/
uint16_t mcp3208_ReadChannel(uint8_t channel_number){
	//#TODO make this more readable...
  unsigned char buff[] = {static_cast<char>(0b110 | ((channel_number & 0b111) >> 2)),
                          static_cast<char>((channel_number & 0b111) << 6),
                          static_cast<char>(0)};

  wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
  return ((buff[1] & 0b1111) << 8) | buff[2];
}

//! Analog read function by Voltage[V]
/*!
  \param adc_pin ADC pin number (0 - 7)
  \return input voltage (0 ~ Vref [V])
*/
double mcp3208_ReadChannelVoltage(uint8_t channel_number){

  uint16_t digitalValue = analogRead(channel_number);
  double voltage = (double)digitalValue * ADC_VOLTAGE_REF / ADC_LEVELS;
  return voltage;
}

//#TODO implment these functions...
void mcp3208_ReadAllChannels(uint16_t* result_buffer){
	
	for(int i=0; i<NUMBER_OF_CHANNELS; i++){
		result_buffer[i] = mcp3208_ReadChannel(i);
	}
	
}
void mcp3208_ReadVoltageAllChannels(double* result_buffer){}
