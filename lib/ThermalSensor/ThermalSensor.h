#ifndef THERMAL_SENSOR_H
#define THERMAL_SENSOR_H

#include "Arduino.h"
#include "Wire.h"
#include <Common.h>


#define MLX90614_I2CADDR 0x5A


// RAM
#define MLX90614_RAWIR1 0x04
#define MLX90614_RAWIR2 0x05
#define MLX90614_TA 0x06 // Ambient
#define MLX90614_TOBJ1 0x07 // Object
#define MLX90614_TOBJ2 0x08


// EEPROM
#define MLX90614_TOMAX 0x20
#define MLX90614_TOMIN 0x21
#define MLX90614_PWMCTRL 0x22
#define MLX90614_TARANGE 0x23
#define MLX90614_EMISS 0x24
#define MLX90614_CONFIG 0x25
#define MLX90614_ADDR 0x0E
#define MLX90614_ID1 0x3C
#define MLX90614_ID2 0x3D
#define MLX90614_ID3 0x3E
#define MLX90614_ID4 0x3F


class ThermalSensor  {
public:
    ThermalSensor() {};
    void init();
    void update();
    void print();
    bool victim[THERMAL_NUM] = {false};
    bool spotHeat(int sensor, int heat);
private:
    void calibrate();
    float value[THERMAL_NUM] = {0};
    float threshold[THERMAL_NUM] = {0};
    bool spot;
};

#endif