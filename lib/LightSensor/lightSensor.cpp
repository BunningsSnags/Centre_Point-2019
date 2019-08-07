#include <arduino.h>
#include <lightSensor.h>
#include <Common.h>

// Light define
value[i] = 0;

void LightSensor::init() {
    
}

void LightSensor::update() {
    value[1] = analogRead(lightValue[1]);
    value[2] = analogRead(lightValue[2]);
    value[3] = analogRead(lightValue[3]);
}

// Printer
void LightSensor::print() {
    for i in LIGHTSENSOR_NUM {
        Serial.println(value[i]);
    }
}