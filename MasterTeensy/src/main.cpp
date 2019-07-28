#include <LRFs.h>
#include <Motors.h>
#include <MPU.h>
#include <ThermalSensor.h>

LRFs lrfs;
Motors motors;
MPU imu;
ThermalSensor thermals;

void receive() {
    if(Serial1.available() >= SLAVE_PACKET_SIZE) {
        uint8_t firstByte = Serial1.read();
        uint8_t secondByte = Serial1.peek();
        if(firstByte == SLAVE_START_BYTE && secondByte == SLAVE_START_BYTE) {
            uint8_t buffer[SLAVE_PACKET_SIZE - 2];
            for(uint8_t i = 0; i < SLAVE_PACKET_SIZE - 2; i++) {
                buffer[i] = Serial1.read();
            }
            lrfs.value[4] = buffer[0] << 8 | buffer[1];
            lrfs.value[5] = buffer[2] << 8 | buffer[3];
            lrfs.value[6] = buffer[4] << 8 | buffer[5];
            lrfs.value[7] = buffer[6] << 8 | buffer[7];
            thermals.victim[2] = buffer[8] == 0 ? false : true;
            thermals.victim[3] = buffer[9] == 0 ? false : true;
        }
    }
}

void setup() {
    #if DEBUG
        Serial.begin(TEENSY_BAUD_RATE);
    #endif
    Serial1.begin(TEENSY_BAUD_RATE);
    lrfs.init();
    motors.init();
    imu.init();
    thermals.init();
}

void loop() {
    lrfs.update();
    motors.update(50, 50);
    imu.update();
    thermals.update();
    receive();
}