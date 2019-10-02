#include <lightSensor.h>

void LightSensor::init() {
    Serial.begin(LIGHT_BAUD_RATE);
}

void LightSensor::update() {
    light[0] = analogRead(FRONT_LEFT_LIGHT);
    light[1] = analogRead(FRONT_RIGHT_LIGHT);
    light[2] = analogRead(BACK_LIGHT);
}

bool LightSensor::spotBlack(int darkness) {
    for(int i = 0; i < 3; i++) {
        if(light[i] < darkness) {
            return true;
        }
        else {
            return false;
        }
    }
}