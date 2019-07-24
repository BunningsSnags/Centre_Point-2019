#ifndef MOTORS_H
#define MOTORS_H

#include <Common.h>

class Motors {
public:
    Motors() {};
    void init();
    void update(uint8_t lrft, uint8_t right);
private:
    uint8_t currentLeft = 0;
    uint8_t currentRight = 0;
};

#endif