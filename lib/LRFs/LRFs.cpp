#include "LRFs.h"

void LRFs::init() {
    #if DEBUG
        Serial.begin(SERIAL_BAUD_RATE);
    #endif
    Serial1.begin(SERIAL_BAUD_RATE);
    Serial2.begin(SERIAL_BAUD_RATE);
    Serial3.begin(SERIAL_BAUD_RATE);
    Serial4.begin(SERIAL_BAUD_RATE);
    Serial5.begin(SERIAL_BAUD_RATE);
    lrfBack1.begin(SERIAL_BAUD_RATE);
    lrfBack2.begin(SERIAL_BAUD_RATE);
    lrfRight1.begin(SERIAL_BAUD_RATE);
}

void LRFs::update() {
    if(Serial1.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = Serial1.read();
        uint8_t secondByte = Serial1.peek();
        if(firstByte == 90 && secondByte == 90) {
            Serial1.read();
            Serial1.read();
            Serial1.read();
            uint8_t high = Serial1.read();
            uint8_t low = Serial1.read();
            value[0] = high << 8 | low;
        }
    }
    if(Serial2.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = Serial2.read();
        uint8_t secondByte = Serial2.peek();
        if(firstByte == 90 && secondByte == 90) {
            Serial2.read();
            Serial2.read();
            Serial2.read();
            uint8_t high = Serial2.read();
            uint8_t low = Serial2.read();
            value[1] = high << 8 | low;
        }
    }
    if(Serial3.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = Serial3.read();
        uint8_t secondByte = Serial3.peek();
        if(firstByte == 90 && secondByte == 90) {
            Serial3.read();
            Serial3.read();
            Serial3.read();
            uint8_t high = Serial3.read();
            uint8_t low = Serial3.read();
            value[2] = high << 8 | low;
        }
    }
    if(Serial4.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = Serial4.read();
        uint8_t secondByte = Serial4.peek();
        if(firstByte == 90 && secondByte == 90) {
            Serial4.read();
            Serial4.read();
            Serial4.read();
            uint8_t high = Serial4.read();
            uint8_t low = Serial4.read();
            value[3] = high << 8 | low;
        }
    }
    if(Serial5.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = Serial5.read();
        uint8_t secondByte = Serial5.peek();
        if(firstByte == 90 && secondByte == 90) {
            Serial5.read();
            Serial5.read();
            Serial5.read();
            uint8_t high = Serial5.read();
            uint8_t low = Serial5.read();
            value[4] = high << 8 | low;
        }
    }
    lrfRight1.listen();
    if(lrfRight1.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = lrfRight1.read();
        uint8_t secondByte = lrfRight1.peek();
        if(firstByte == 90 && secondByte == 90) {
            lrfRight1.read();
            lrfRight1.read();
            lrfRight1.read();
            uint8_t high = lrfRight1.read();
            uint8_t low = lrfRight1.read();
            value[5] = high << 8 | low;
        }
    }
    lrfBack1.listen();
    if(lrfBack1.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = lrfBack1.read();
        uint8_t secondByte = lrfBack1.peek();
        if(firstByte == 90 && secondByte == 90) {
            lrfBack1.read();
            lrfBack1.read();
            lrfBack1.read();
            uint8_t high = lrfBack1.read();
            uint8_t low = lrfBack1.read();
            value[6] = high << 8 | low;
        }
    }
    lrfBack2.listen();
    if(lrfBack2.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = lrfBack2.read();
        uint8_t secondByte = lrfBack2.peek();
        if(firstByte == 90 && secondByte == 90) {
            lrfBack2.read();
            lrfBack2.read();
            lrfBack2.read();
            uint8_t high = lrfBack2.read();
            uint8_t low = lrfBack2.read();
            value[7] = high << 8 | low;
        }
    }
}