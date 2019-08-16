#include <StepperMotor.h>

void StepperMotor::init() {
    Serial.begin(STEPPER_BAUD_RATE);
    pinMode(INONE, OUTPUT); 
    pinMode(INTWO, OUTPUT); 
    pinMode(INTHREE, OUTPUT); 
    pinMode(INFOUR, OUTPUT); 
}

void StepperMotor::cube(int amount) {
    
}