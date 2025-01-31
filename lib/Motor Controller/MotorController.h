#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_
#include <Common.h>
#include "Tile.h"

class MotorController {
public:
    MotorController() {}
    void init();
    void update(int16_t left, int16_t right, int16_t rotation);
    Tile avoidTile(Tile currentTile, bool direction);
    bool setOrientation(int ofSet);
};

#endif // MOTOR_CONTROLLER_H_