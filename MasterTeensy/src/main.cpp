#include <MotorController.h>
#include <LRFs.h>

MotorController motors;
LRFs lrfs;

int speed = 0;
int tiletime = 0;

void lrfPrint() {
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(lrfs.value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, ");
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
    lrfs.update();
    // lrfPrint();
    while(lrfs.value[0] > 200) {
        lrfs.update();
        motors.update(100, 100);
    }
    motors.update(-150, 150);
}