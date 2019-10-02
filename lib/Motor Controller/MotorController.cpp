#include "MotorController.h"

void MotorController::init() {
    pinMode(LEFT_PWM, OUTPUT);
    pinMode(LEFT_INONE, OUTPUT);
    pinMode(LEFT_INTWO, OUTPUT);

    pinMode(RIGHT_PWM, OUTPUT);
    pinMode(RIGHT_INONE, OUTPUT);
    pinMode(RIGHT_INTWO, OUTPUT);
}

// void avoidTile() {
    
// }

void MotorController::update(int16_t left, int16_t right, int16_t rotation) {

    // Serial.printf("Left: %d - %d = %d\n", left, rotation, left - rotation);
    // Serial.printf("Right: %d + %d = %d\n", right, rotation, right + rotation);

    left = left - rotation;
    right = right + rotation;

    right = min(right, 255);
    right = max(right, -255);

    left = min(left, 255);
    left = max(left, -255);
    // Serial.printf("Left: %d, Right: %d\n", right, left);


    if(left > 0) {
        digitalWrite(LEFT_INONE, HIGH);
        digitalWrite(LEFT_INTWO, LOW);
        analogWrite(LEFT_PWM, abs(left));
    } else if(left < 0) {
        digitalWrite(LEFT_INONE, LOW);
        digitalWrite(LEFT_INTWO, HIGH);
        analogWrite(LEFT_PWM, abs(left));
    } else {
        digitalWrite(LEFT_INONE, HIGH);
        digitalWrite(LEFT_INTWO, HIGH);
        analogWrite(LEFT_PWM, abs(left));
    }

    if(right > 0) {
        digitalWrite(RIGHT_INONE, HIGH);
        digitalWrite(RIGHT_INTWO, LOW);
        analogWrite(RIGHT_PWM, abs(right));
    } else if(right < 0) {
        digitalWrite(RIGHT_INONE, LOW);
        digitalWrite(RIGHT_INTWO, HIGH);
        analogWrite(RIGHT_PWM, abs(right));
    } else {
        digitalWrite(RIGHT_INONE, HIGH);
        digitalWrite(RIGHT_INTWO, HIGH);
        analogWrite(RIGHT_PWM, abs(right));
    }
}

bool MotorController::setOrientation(int ofSet) {
    if(fabs(ofSet) < 100) {
        return true;
    }
    else {
        update(0, 0, ofSet);
        return false;
    }
}