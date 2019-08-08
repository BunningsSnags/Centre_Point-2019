#include <MotorController.h>
#include <LRFs.h>
#include <lightSensor.h>

MotorController motors;
LRFs lrfs;
LightSensor light;

int moving = 1;

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
// Debuging function
void debuger(int debug) {
    if(debug == 1) {
        lrfPrint();
    }
    if(debug == 2) {
        lightPrint();
    }
}

void tileMove(int direction) {
    if(direction == 1) {
        // moving = true;
        while(moving == 1) {
            motors.update(100, 100);
            delay(TILE_DIST_TIME);
            moving = 0;
        }
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
    lrfs.update();
    debuger(1);
    // Debuging
    // while(true) {
    //     debuger(1);
    //     lrfs.update();
    //     light.update();
    // }
    while(lrfs.value[0] > 150) {
        debuger(1);
        lrfs.update();
        motors.update(100, 100);
    }
    if(lrfs.value[2] > 100) {
        motors.update(-100, 100);
    }
    if(lrfs.value[3] > 100) {
        motors.update(100, -100);
    } 
    if(lrfs.value[3] < 100 && lrfs.value[2] < 100) {
        motors.update(-100, 100);   
    }
}