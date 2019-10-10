#ifndef LOGIC_H_
#define LOGIC_H_

#include <Common.h>

// ============ Includes ============
#include <LRFs.h>
#include <MotorController.h>
#include <Timer.h>
#include <LightSensor.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <MPU.h>
#include <PID.h>
#include <Tile.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

class Logic {
public:
    
    Logic() {}

    // ============ Setups ============
    LRFs lrfs;
    MotorController motors;
    LightSensor light;
    MPU imu;
    PID IMUPID = PID(15, 0, 0, 255*2);
    PID LRFPID = PID(1, 0, -1.5, 255*2);
    Tile curTile;

    // ============ Functions ============
    void Navigate();
    void Record();
    void update();

private:
    int lrfInput();
};

#endif