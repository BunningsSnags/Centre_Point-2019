#include <MotorController.h>
#include <LRFs.h>

MotorController motors;
LRFs lrfs;

void lrfPrint() {
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(lrfs.value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, ");
}

void setup() {
    motors.init();
    lrfs.init();
}

void tileMove(char direction) {
    if(direction == "forward") {
        motors.update(100, 100);
        delay(TILE_DIST_SEC)
    } else if(direction == "back") {
        motors.update(-100, -100);
        delay(TILE_DIST_SEC)
    } else if(direction == "left") {
        motors.update(-100, 100);
        //Function for imu degrees(TILE_TURN_DEG)
    } else if(direction == "right") {
        motors.update(-100, 100);
        //Function for imu degrees(TILE_TURN_DEG)
    } else {
        Serial.printnl('Unknown direction, please use:')
        Serial.printnl('"forward", "back", "left" or "right"')
    }
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