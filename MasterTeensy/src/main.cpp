#include <MotorController.h>

MotorController motors;

void setup() {
    motors.init();
}

void loop() {
    motors.update(-255, 255);
}