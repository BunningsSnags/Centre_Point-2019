#include <MotorController.h>

MotorController motors;

void setup() {
    motors.init();
}

void loop() {
    motors.update(100, 100);
    delay(4000);
    motors.update(-100, 100);
    delay(2000);
    motors.update(-100, -100);
    delay(4000);
    motors.update(100, -100);
    delay(2000)
}