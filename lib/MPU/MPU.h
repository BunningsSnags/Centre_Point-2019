#ifndef MPU_H
#define MPU_H

#include <I2C.h>
#include <Common.h>

class MPU {
public:
    MPU() {};
    void init();
    void update();
    float horizontalHeading;
    float verticalHeading;
private:
    Vector3D readGyroscope();
    void calibrate();
    float convertRawGyro(int raw);
    long previousTimeGyro;
    long previousDrift;
    float horizontalCalibrationGyro;
    float verticalCalibrationGyro;
    float horizontalDrift = 0;
    float verticalDrift = 0;
};

#endif
