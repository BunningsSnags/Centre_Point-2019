#include <MotorController.h>
#include <LRFs.h>
#include <MPU.h>

MotorController motors;
LRFs lrfs;
MPU imu;
LightSensor light;

int speed = 0;
int tiletime = 0;

// ============ Debugers ============
void debuger(char debug) {
    if(debug == 'lrf') {
        lrfPrint();
    }
    if(debug == 'imu') {
        imuPrint();
    }
    if(debug == 'light') {
        lightPrint();
    }
}
// LRF
void lrfPrint() {
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(lrfs.value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, Front-Right, Left-Front, Right-Front, Left-Back, Right-Back, Back-Left, Back-Right");
}
// Light Sensor
void lightPrint() {
    for i in LIGHTSENSOR_NUM {
        Serial.println(value[i]);
    }
}
// IMU
void imuPrint() {
    MPU::readGyroscope()
}

void tileMove(int direction) {
    if(direction == 1) {
        motors.update(100, 100);
        delay(TILE_DIST_TIME);
    } else if(direction == 2) {
        motors.update(-100, -100);
        delay(TILE_DIST_TIME);
    } else if(direction == 3) {
        motors.update(-100, 100);
        //Function for imu degrees(TILE_TURN_DEG)
    } else if(direction == 4) {
        motors.update(100, -100);
        //Function for imu degrees(TILE_TURN_DEG)
    }
}

void setup() {
    motors.init();
    lrfs.init();
}

void loop() {
    // Debuging
    while(true) {
        bebuger(lrf);
        lrfs.update();
        imu.update();
    }
    while(lrfs.value[0] > 200) {
        motors.update(100, 100);
    }
    motors.update(-150, 150);
}