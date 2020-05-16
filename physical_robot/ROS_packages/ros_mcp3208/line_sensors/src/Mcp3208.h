#include <stdint.h>

#define ADC_VOLTAGE_REF 3.3
#define SPI_CHANNEL 0
#define SPI_SPEED 245000
#define NUMBER_OF_CHANNELS 8

void mcp3208_spi_init();

uint16_t mcp3208_ReadChannel(uint8_t channel_number);
double mcp3208_ReadChannelVoltage(uint8_t channel_number);

void mcp3208_ReadAllChannels(uint16_t* result_buffer);
void mcp3208_ReadVoltageAllChannels(double* result_buffer);
