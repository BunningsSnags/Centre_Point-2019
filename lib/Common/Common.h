#ifndef COMMON_H_
#define COMMON_H_

#include <Pins.h>
#include <Colours.h>
#include <Arduino.h>


// Debug
#define DEBUG false
#define TEENSY_BAUD_RATE 9600
#define MASTER_BLINK 1000
#define SLAVE_BLINK 500


// Communications
#define SLAVE_PACKET_SIZE 10
#define SLAVE_START_BYTE 255


// LRFs
#define LRF_BAUD_RATE 9600
#define LRF_NUM 8
#define LRF_PACKET_SIZE 8


// Tile Spacing
#define TILE_SIZE 300
#define TILE_DIST_TIME 1550
#define TILE_TURN_TIME
#define TILE_TURN_DEG


// Light Sensor
#define LIGHT_BAUD_RATE 9600
#define LIGHTSENSOR_NUM 3
#define LIGHT_VALUE_START 0


// RGB Leds
#define NUM_RGB_LEDS 60
#define RGB_PIN 23
#define LED_BLINK 500


// Stepper
#define STEPPER_BAUD_RATE 115200


//MPU
#define MPU_CALIBRATION_COUNT 40
#define MPU_CALIBRATION_TIME 100
#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C
#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18
#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

// Thermal Sensors
#define THERMAL_NUM 4
#define THERMAL_CALIBRATION_COUNT 5
#define THERMAL_CALIBRATION_TIME 50

// Motor
#define SPEED 150

// ==== Debug and functions =====
// LEDS

// Debug
#define dLrfs 1
#define dLight 2
#define dTherm 3
#define dImu 4
#define dCorrect 5
#define dWall 6


struct Coordinate {
    int8_t x;
    int8_t y;
    int8_t z;
};

struct Vector3D {
	float x;
	float y;
	float z;
};

float floatMod(float x, float m);
int mod(int x, int m);

#endif