#include "MPU.h"

void MPU::init() {
    Wire.begin();
    I2CwriteByte(MPU9250_ADDRESS, 29, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 26, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_1000_DPS);
    I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_2_G);
    I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
    I2CwriteByte(MAG_ADDRESS, 0x0A, 0x16);
    previousTimeGyro = micros();
    calibrate();
}

Vector3D MPU::readGyroscope() {
    uint8_t buffer[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, buffer);
    int16_t gx = -(buffer[8] << 8 | buffer[1]);
    int16_t gy = -(buffer[10] << 8 | buffer[11]);
    int16_t gz = buffer[12] << 8 | buffer[13];
    Vector3D returnVector = {convertRawGyro(gx), convertRawGyro(gy), convertRawGyro(gz)};
    return returnVector;
}

void MPU::update() {
    Vector3D vector = readGyroscope();
	long currentTime = micros();
    horizontalHeading += -(((float)(currentTime - previousTimeGyro) / 1000000.0) * (vector.z - horizontalCalibrationGyro));
    verticalHeading += -(((float)(currentTime - previousTimeGyro) / 1000000.0) * (vector.y - verticalCalibrationGyro));
    previousTimeGyro = currentTime;
    if(millis() - previousDrift > 100) {
        horizontalHeading += horizontalDrift;
        verticalHeading += verticalDrift;
        previousDrift = millis();
    }
	horizontalHeading = floatMod(horizontalHeading, 360);
    verticalHeading = floatMod(verticalHeading, 360);
    delay(10);
}

void MPU::calibrate() {
    for(uint8_t i = 0; i < MPU_CALIBRATION_COUNT; i++) {
        Vector3D readingGyro = readGyroscope();
        horizontalCalibrationGyro += readingGyro.z;
        verticalCalibrationGyro += readingGyro.y;
        delay(MPU_CALIBRATION_TIME);
    }
    horizontalCalibrationGyro /= MPU_CALIBRATION_COUNT;
    verticalCalibrationGyro /= MPU_CALIBRATION_COUNT;
    update();
    float horizontal = horizontalHeading;
    float vertical = verticalHeading;
    delay(100);
    update();
    horizontalDrift = horizontalHeading - horizontal;
    verticalDrift = verticalHeading - vertical;
    previousDrift = millis();
}

float MPU::convertRawGyro(int raw) {
    return ((raw * 1000.0) / 32768.0);
}