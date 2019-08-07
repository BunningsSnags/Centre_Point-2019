#include <MotorController.h>
#include <LRFs.h>
#include <lightSensor.h>

MotorController motors;
LRFs lrfs;
LightSensor light;

int speed = 0;
int tiletime = 0;

// ============ Debugers ============
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
    for(int i = 0; i < LIGHTSENSOR_NUM; i++) {
        Serial.println(light.light[i]);
    }
}

void debuger(char debug) {
    if(debug == 'lrf') {
        lrfPrint();
    }
    if(debug == 'light') {
        lightPrint();
    }
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
    light.init();
}

void loop() {
    // Debuging
    while(true) {
        // debuger(lrf);
        lrfs.update();
        light.update();
    }
    while(lrfs.value[0] > 200) {
        motors.update(100, 100);
    }
    motors.update(-150, 150);
}