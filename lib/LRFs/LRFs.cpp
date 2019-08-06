#include "LRFs.h"

void LRFs::init() {
    Serial2.begin(LRF_BAUD_RATE);
    Serial3.begin(LRF_BAUD_RATE);
    Serial4.begin(LRF_BAUD_RATE);
    Serial5.begin(LRF_BAUD_RATE);
}

void LRFs::print(){
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, Front-Right, Left-Left, Left-Right, Back-Left, Back-Right, Right-Left, Right-Right");
}

HardwareSerial serials[] = {Serial2, Serial3, Serial4, Serial5};
void LRFs::update() {
    for(int i = 0; i < LRF_NUM; i++) {
        if(serials.available()>=8){
        int firstbyte = serials.read();
            if(firstbyte == 90){
                if(serials.read()==firstbyte){t4g
                    serials.read();
                    serials.read();
                    int highbyte = serials.read();
                    int lowbyte = serials.read();
                    value[i] = highbyte << 8 | lowbyte;
                }
            }
        }
    }
}