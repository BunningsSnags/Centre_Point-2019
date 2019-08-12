#include <arduino.h>
#include <Common.h>

class StepperMotor {
public:
    void init();
    void cube(int amount);
private:
    int REVOLUTION_STEP_NUM = 258;
    int CUBE_STEP = 16.125;
};