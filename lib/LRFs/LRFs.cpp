#include "LRFs.h"

void LRFs::init() {
    Serial2.begin(LRF_BAUD_RATE);
    Serial3.begin(LRF_BAUD_RATE);
    Serial4.begin(LRF_BAUD_RATE);
    Serial5.begin(LRF_BAUD_RATE);
}

uint16_t LRFs::average(int lrf1, int lrf2) {
    uint16_t averaged = (value[lrf1] + value[lrf2])/2;
    return averaged;
}

// HardwareSerial Serial2[] = {Serial2, Serial3, Serial4, Serial5};
void LRFs::update() {
    while(Serial2.available() >= LRF_PACKET_SIZE) {
        uint8_t firstbyte = Serial2.read();
        uint8_t secondbyte = Serial2.peek();
        if(firstbyte == 90 && secondbyte == 90) {
            Serial2.read();
            Serial2.read();
            Serial2.read();
            uint8_t highbyte = Serial2.read();
            uint8_t lowbyte = Serial2.read();
            value[0] = highbyte << 8 | lowbyte;
        }
    }
    while(Serial3.available() >= LRF_PACKET_SIZE) {
        uint8_t firstbyte = Serial3.read();
        uint8_t secondbyte = Serial3.peek();
        if(firstbyte == 90 && secondbyte == 90) {
            Serial3.read();
            Serial3.read();
            Serial3.read();
            uint8_t highbyte = Serial3.read();
            uint8_t lowbyte = Serial3.read();
            value[1] = highbyte << 8 | lowbyte;
        }
    }
    while(Serial4.available() >= LRF_PACKET_SIZE) {
        uint8_t firstbyte = Serial4.read();
        uint8_t secondbyte = Serial4.peek();
        if(firstbyte == 90 && secondbyte == 90) {
            Serial4.read();
            Serial4.read();
            Serial4.read();
            uint8_t highbyte = Serial4.read();
            uint8_t lowbyte = Serial4.read();
            value[2] = highbyte << 8 | lowbyte;
        }
    }
    while(Serial5.available() >= LRF_PACKET_SIZE) {
        uint8_t firstbyte = Serial5.read();
        uint8_t secondbyte = Serial5.peek();
        if(firstbyte == 90 && secondbyte == 90) {
            Serial5.read();
            Serial5.read();
            Serial5.read();
            uint8_t highbyte = Serial5.read();
            uint8_t lowbyte = Serial5.read();
            value[3] = highbyte << 8 | lowbyte;
        }
    }
}