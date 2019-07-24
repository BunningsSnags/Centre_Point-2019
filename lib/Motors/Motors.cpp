#include "Motors.h"

void Motors::init() {
    pinMode(RIGHT_PWM, OUTPUT);
    pinMode(RIGHT_INONE, OUTPUT);
    pinMode(RIGHT_INTWO, OUTPUT);
    pinMode(LEFT_PWM, OUTPUT);
    pinMode(LEFT_INONE, OUTPUT);
    pinMode(LEFT_INTWO, OUTPUT);
}

void Motors::update(uint8_t left, uint8_t right) {
    if(currentLeft != left) {
        bool dirOneWrite = true;
        bool dirTwoWrite = true;
        uint8_t pwmWrite = 0;
        if(left * 2.55 != 0) {
            pwmWrite = min(abs(left * 2.55), 255);
            dirOneWrite = left > 0;
            dirTwoWrite = !dirOneWrite;
        }
        digitalWrite(LEFT_INONE, dirOneWrite);
        digitalWrite(LEFT_INTWO, dirTwoWrite);
        analogWrite(LEFT_PWM, pwmWrite);
        currentLeft = left;
    }
    if(currentRight != right) {
        bool dirOneWrite = true;
        bool dirTwoWrite = true;
        uint8_t pwmWrite = 0;
        if(right * 2.55 != 0) {
            pwmWrite = min(abs(right * 2.55), 255);
            dirOneWrite = right > 0;
            dirTwoWrite = !dirOneWrite;
        }
        digitalWrite(RIGHT_INONE, dirOneWrite);
        digitalWrite(RIGHT_INTWO, dirTwoWrite);
        analogWrite(RIGHT_PWM, pwmWrite);
        currentRight = right;
    }
}