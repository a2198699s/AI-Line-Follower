#ifndef PARAMETERS_H
#define PARAMETERS_H

#endif // PARAMETERS_H

#define STEPSCOUNT 1000
#define RUNSCOUNT 10

#define LEARNINGRATECOUNT 5

// Predictor Array
#define ROW1P 12
#define ROW1N 8
#define ROW1S 3

#define ROW2P 14
#define ROW2N 6
#define ROW2S 3

#define ROW3P 16
#define ROW3N 2
#define ROW3S 6

// Error Arrays
#define SENSORLEFT 7
#define SENSORRIGHT -7

// Filter Specifications
#define NFILTERS 5
#define MINT 3 //3
#define MAXT 10 //10
#define DAMPINGCOEFF 0.51

// Network Structure
#define LEARNINGRATE 0.1
#define DESIREDLEARNINGRATE 0.01

#define NLAYERS 3
    #define N1 12
    #define N2 6
    #define N3 1 // has to always be one

// Robot speed
#define SPEED 90 // for reflex it is 60
#define ERRORGAIN 200 // for reflex it is 200

#define NETWORKGAIN 10
#define PREDGAIN 100


