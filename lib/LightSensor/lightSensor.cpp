#include <lightSensor.h>

void LightSensor::init() {
    Serial.begin(LIGHT_BAUD_RATE);
}

void LightSensor::update() {
    light[0] = analogRead(FRONT_LEFT_LIGHT);
    light[1] = analogRead(FRONT_RIGHT_LIGHT);
    light[2] = analogRead(BACK_LIGHT);
}

Tile LightSensor::spotBlack(int darkness, Tile tile) {
    for(int i = 0; i < 3; i++) {
        if(light[i] > darkness) {
            tile.isBlack = true;
            return tile;
        }
        else {
            tile.isBlack = false;
            return tile;
        }
    }
}

Tile LightSensor::spotSilver(int brightness, Tile tile) {
    for(int i = 0; i < 3; i++) {
        if(light[i] < brightness) {
            tile.isSilver = true;
            return tile;
        }
        else {
            tile.isSilver = false;
            return tile;
        }
    }
}