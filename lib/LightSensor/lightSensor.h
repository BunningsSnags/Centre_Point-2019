#include <Common.h>

class LightSensor {
public:
    void init();
    void update();
    int light[LIGHTSENSOR_NUM] = {0};
    Tile spotBlack(int darkness, Tile tile);
    Tile spotSilver(int brightness, Tile tile);
};