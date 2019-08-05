#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_
#include <Common.h>

class MotorController {
public:
    MotorController() {}
    void init();
    void update(int16_t left, int16_t right);
};

#endif // MOTOR_CONTROLLER_H_