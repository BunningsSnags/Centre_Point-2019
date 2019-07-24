#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

#define DEBUG true

#define SERIAL_BAUD_RATE 9600

// ----------- LRF Stuff -----------
#define HARDWARE_LRFS_NUM 3
#define LRF_PACKET_SIZE 8
#define LRF_NUM 3
// #define SOFTWARE_LRFS_NUM 5

// ----------- Motor Defines -----------
#define RIGHT_PWM 2
#define RIGHT_INONE 26
#define RIGHT_INTWO 27
#define LEFT_PWM 3
#define LEFT_INONE 28
#define LEFT_INTWO 29

// ----------- Stepper Motors -----------
#define STEP_PWM
#define STEP_INONE
#define STEP_INTWO
#define STEP_

// ----------- Light Sensor -----------
#define frontLight A0
#define backLight A1

// ----------- unknown -----------
struct Coordinate {
    float x;
    float y;
    float z;
};

// ----------- Camera Stuff -----------

// ----------- Arrays -----------
#define WIDTH 10
#define HEIGHT 10

#endif