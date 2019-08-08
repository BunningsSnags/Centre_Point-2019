// ============ Includes ============
#include <LRFs.h>
#include <MotorController.h>
#include <MPU.h>
#include <ThermalSensor.h>
#include <Timer.h>
// #include <LEDs.h>
#include <LightSensor.h>
#include <Arduino.h>

// ============ Setups ============
LRFs lrfs;
MotorController motors;
MPU imu;
ThermalSensor thermals;
LightSensor light;
// ------------ Timers ------------
Timer cubeTimer(80000);
Timer turnTimer(1000000);
Timer LEDTimer(800000);
bool ledOn = false;

    // ------------ Main Flash ------------
void teensyFlash() {
    if(LEDTimer.timeHasPassed()){
        digitalWrite(TEENSY_LED, ledOn);
        ledOn = !ledOn;
    }
}

// ============ algorithms ============


// ============ Slave Teensy ============
void receive() {
    if(Serial1.available() >= SLAVE_PACKET_SIZE) {
        uint8_t firstByte = Serial1.read();
        uint8_t secondByte = Serial1.peek();
        if(firstByte == SLAVE_START_BYTE && secondByte == SLAVE_START_BYTE) {
            uint8_t buffer[SLAVE_PACKET_SIZE - 2];
            for(uint8_t i = 0; i < SLAVE_PACKET_SIZE - 2; i++) {
                buffer[i] = Serial1.read();
            }
            lrfs.value[4] = buffer[0] << 8 | buffer[1];
            lrfs.value[5] = buffer[2] << 8 | buffer[3];
            lrfs.value[6] = buffer[4] << 8 | buffer[5];
            lrfs.value[7] = buffer[6] << 8 | buffer[7];
            thermals.victim[2] = buffer[8] == 0 ? false : true;
            thermals.victim[3] = buffer[9] == 0 ? false : true;
        }
    }
}

// ============ Setup ============
void setup() {
    #if DEBUG
        Serial.begin(TEENSY_BAUD_RATE);
    #endif
    Serial1.begin(TEENSY_BAUD_RATE);
    lrfs.init();
    motors.init();
    imu.init();
    thermals.init();
    pinMode(TEENSY_LED, OUTPUT);
    digitalWrite(TEENSY_LED, HIGH);
    digitalWrite(TEENSY_LED, LOW);
}

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

// Tile Move
// void tileMove(int direction) {
//     if(direction == 1) {
//         // moving = true;
//         while(moving == 1) {
//             tileMove = {
//                 motors.update(100, 100);
//                 delay(TILE_DIST_TIME);
//             }
//             moving = 0;
//         }
//         return tileMove;
//     }
// }



void loop() {
    // ------------ updates ------------
    lrfs.update();
    thermals.update();
    light.update();
    debuger(1);
    teensyFlash();
    // tileMove(1)
    // while(lrfs.value[0] > 150 && lrfs.value[1] > 150) {
    //     debuger(1);
    //     lrfs.update();
    //     motors.update(-50, -50);
    // }
    // if(lrfs.value[2] > 200) {
    //     motors.update(-75, 75);
    // }
    // if(lrfs.value[3] > 200) {
    //     motors.update(75, -75);
    // }
    // if(lrfs.value[2] < 200 && lrfs.value[3] < 200) {
    //     motors.update(75, -75);
    // }
}