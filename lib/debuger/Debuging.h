#include <Common.h>
#include <LRF.h>
#include <lightSensor.h>
#include <ThermalSensor_Bus1.h>
#include <ThermalSensor_Bus2.h>

class debuger {
public:
    debuger() {}
    void debug(int sensor);
private:
    int sensor = 0;
};