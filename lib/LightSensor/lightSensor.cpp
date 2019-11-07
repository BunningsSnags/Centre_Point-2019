#include <lightSensor.h>

void LightSensor::init() {
    Serial.begin(LIGHT_BAUD_RATE);
    light[0] = 0;
    light[1] = 0;
    light[2] = 0;
}

void LightSensor::update() {
    light[0] = analogRead(FRONT_LEFT_LIGHT);
    light[1] = analogRead(FRONT_RIGHT_LIGHT);
    light[2] = analogRead(BACK_LIGHT);
}

bool LightSensor::spotBlack(int darkness) {
    for(int i = 0; i < LIGHTSENSOR_NUM; i++) {
        if(light[i] > darkness) {
            isBlack = true;
        }
        else {
            isBlack = false;
        }
    }
    return isBlack;
}

Tile LightSensor::spotSilver(int brightness, Tile tile) {
    for(int i = 0; i < 3; i++) {
        if(light[i] < brightness) {
            tile.isSilver = true;
        }
        else {
            tile.isSilver = false;
        }
    }
    return tile;
}