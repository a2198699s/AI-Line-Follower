#include <stdint.h>

#define BINARY_THRESHOLD 1.5


void reorderValues(uint16_t* sensor_values);

void printArray(uint16_t* array_values);

uint16_t getArrayAverage(uint16_t* array_values);

void makeBinaryLine(uint16_t* bin_line, uint16_t* sensor_values);
