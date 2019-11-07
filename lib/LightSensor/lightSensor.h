#include <Common.h>

class LightSensor {
public:
    void init();
    void update();
    int light[LIGHTSENSOR_NUM] = {0};
    bool spotBlack(int darkness);
    Tile spotSilver(int brightness, Tile tile);
private:
    bool isBlack = false;
};