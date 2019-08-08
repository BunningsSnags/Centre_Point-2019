#include <LRFs.h>
#include <ThermalSensor.h>

LRFs lrfs;
ThermalSensor thermals;

void send() {
    Serial1.write(SLAVE_START_BYTE);
    Serial1.write(SLAVE_START_BYTE);
    Serial1.write(highByte(lrfs.value[0]));
    Serial1.write(lowByte(lrfs.value[0]));
    Serial1.write(highByte(lrfs.value[1]));
    Serial1.write(lowByte(lrfs.value[1]));
    Serial1.write(highByte(lrfs.value[2]));
    Serial1.write(lowByte(lrfs.value[2]));
    Serial1.write(highByte(lrfs.value[3]));
    Serial1.write(lowByte(lrfs.value[3]));
    Serial1.write(thermals.victim[0]);
    Serial1.write(thermals.victim[1]);
}

void setup() {
    #if DEBUG
        Serial.begin(TEENSY_BAUD_RATE);
    #endif
    Serial1.begin(TEENSY_BAUD_RATE);
    lrfs.init();
    thermals.init();
}

void loop() {
    lrfs.update();
    thermals.update();
}