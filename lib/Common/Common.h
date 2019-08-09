#ifndef COMMON_H_
#define COMMON_H_

#include <Pins.h>
#include <Arduino.h>


// Debug
#define DEBUG false
#define TEENSY_BAUD_RATE 9600
#define MASTER_BLINK 1000
#define SLAVE_BLINK 500


// Communications
#define SLAVE_PACKET_SIZE 12
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
#define NUM_LEDS 5
#define DATA_PIN 23

struct Coordinate {
    int8_t x;
    int8_t y;
    int8_t z;
};

#endif