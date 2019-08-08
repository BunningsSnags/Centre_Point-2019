#include <LEDs.h>

void LEDs::init() {
    pinMode(RGB_LED, OUTPUT);
}

void LEDs::setColour(int red, int green, int blue) {
    analogWrite(RGB_LED, red);
    analogWrite(RGB_LED, green);
    analogWrite(RGB_LED, blue);
}