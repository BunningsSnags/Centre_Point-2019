#include "LRFs.h"

void LRFs::init() {
    Serial2.begin(LRF_BAUD_RATE);
    Serial3.begin(LRF_BAUD_RATE);
    Serial4.begin(LRF_BAUD_RATE);
    Serial5.begin(LRF_BAUD_RATE);
}

    // ------------ LRF Print ------------
void LRFs::print(){
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, Front-Right, Left-Left, Left-Right, Back-Left, Back-Right, Right-Left, Right-Right");
}

int LRFs::average(uint8_t lrf1, uint8_t lrf2){
   return (lrf1 + lrf2)/2
}

void LRFs::update() {
    if(Serial2.available() >= LRF_PACKET_SIZE) {
        uint8_t firstByte = Serial2.read();
        uint8_t secondByte = Serial2.peek();
        if(firstByte == 90 && secondByte == 90) {
            Serial2.read();
            Serial2.read();
            Serial2.read();
            uint8_t high = Serial2.read();
            uint8_t low = Serial2.read();
            value[0] = high << 8 | low;
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
            value[1] = high << 8 | low;
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
            value[2] = high << 8 | low;
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
            value[3] = high << 8 | low;
        }
    }
}