#ifndef COMMON_H_
#define COMMON_H_

#include <Pins.h>
#include <Arduino.h>


// Debug
#define DEBUG false
#define TEENSY_BAUD_RATE 9600


// Communications
#define SLAVE_PACKET_SIZE 12
#define SLAVE_START_BYTE 255


// LRFs
#define LRF_BAUD_RATE 9600
#define LRF_NUM 8
#define LRF_PACKET_SIZE 8


//MPU
#define MPU_CALIBRATION_COUNT 20
#define MPU_CALIBRATION_TIME 50
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
#define NUM_LEDS 5
#define DATA_PIN 23

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

#endif