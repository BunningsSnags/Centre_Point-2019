#include <Common.h>

class LightSensor {
public:
    void init();
    void update();
    int light[LIGHTSENSOR_NUM] = {0};
};