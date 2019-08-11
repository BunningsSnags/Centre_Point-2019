#include "MotorController.h"

void MotorController::init() {
    pinMode(LEFT_PWM, OUTPUT);
    pinMode(LEFT_INONE, OUTPUT);
    pinMode(LEFT_INTWO, OUTPUT);

    pinMode(RIGHT_PWM, OUTPUT);
    pinMode(RIGHT_INONE, OUTPUT);
    pinMode(RIGHT_INTWO, OUTPUT);
}

void MotorController::update(int16_t left, int16_t right) {
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