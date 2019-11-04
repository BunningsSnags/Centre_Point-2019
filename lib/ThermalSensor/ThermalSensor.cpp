#include "ThermalSensor.h"

void ThermalSensor::init() {
    Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_37_38, I2C_PULLUP_INT, 400000);
    Wire2.begin(I2C_MASTER, 0x00, I2C_PINS_3_4, I2C_PULLUP_INT, 400000);
    calibrate();
}

void ThermalSensor::update() {
    Wire1.beginTransmission(MLX90614_I2CADDR);
    Wire1.write(MLX90614_TA);
    Wire1.endTransmission(false);
    Wire1.requestFrom(MLX90614_I2CADDR, (size_t)3);
    uint16_t temp = Wire1.read();
    temp |= Wire1.read() << 8;
    Wire1.read();
    value[0] = (float)(temp * 0.02);
    value[0] -= 273.15;
    victim[0] = (value[0] > threshold[0]);

    Wire2.beginTransmission(MLX90614_I2CADDR);
    Wire2.write(MLX90614_TA);
    Wire2.endTransmission(false);
    Wire2.requestFrom(MLX90614_I2CADDR, (size_t)3);
    temp = Wire2.read();
    temp |= Wire2.read() << 8;
    Wire2.read();
    value[1] = (float)(temp * 0.02);
    value[1] -= 273.15;
    victim[1] = (value[1] > threshold[1]);
}

bool ThermalSensor::spotHeat(int heat) {
    for(int i = 0; i < 4; i++) {
        if(value[i] >= heat) {
            spot = true;
        }
        if(value[i] < heat) {
            spot = false;
        }
        return spot;
    }
}

void ThermalSensor::calibrate() {
    for(uint8_t i = 0; i < THERMAL_CALIBRATION_COUNT; i++) {
        update();
        threshold[0] += value[0];
        threshold[1] += value[1];
        delay(THERMAL_CALIBRATION_TIME);
    }
    threshold[0] /= THERMAL_CALIBRATION_COUNT;
    threshold[0] += 10;
    threshold[1] /= THERMAL_CALIBRATION_COUNT;
    threshold[1] += 10;
}