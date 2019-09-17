#include <LRFs.h>
#include <ThermalSensor.h>
#include <Timer.h>
#include <Pins.h>

LRFs lrfs;
Timer ledTimer(SLAVE_BLINK);

bool ledOn = true;
void slaveFlash() {
    if(ledTimer.timeHasPassed()){
        digitalWrite(SLAVE_LED, ledOn);
        ledOn = !ledOn;
    }
}

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
}

void setup() {
    #if DEBUG
        Serial.begin(TEENSY_BAUD_RATE);
    #endif
    Serial1.begin(TEENSY_BAUD_RATE);
    lrfs.init();
    pinMode(SLAVE_LED, OUTPUT);
}

void loop() {
    lrfs.update();
    slaveFlash();
    send();
}