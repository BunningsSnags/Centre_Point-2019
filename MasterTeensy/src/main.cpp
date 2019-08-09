// ============ Includes ============
#include <LRFs.h>
#include <MotorController.h>
// #include <MPU.h>
// #include <ThermalSensor.h>
#include <Timer.h>
#include <LightSensor.h>

// ============ Setups ============
LRFs lrfs;
MotorController motors;
// MPU imu;
// ThermalSensor thermals;
LightSensor light;
// ------------ Timers ------------
Timer cubeTimer(80000);
Timer turnTimer(1000000);
Timer ledTimer(800000);
bool ledOn = false;
void masterFlash() {
    if(ledTimer.timeHasPassed()){
        digitalWrite(MASTER_LED, ledOn);
        ledOn = !ledOn;
    }
}
void rgbFlash(int flash) {
    if(flash == 1) {
        if(cubeTimer.timeHasPassed()){
            // for(int i = 1; i < leds[NUM_LEDS]; i++) {
            //     led[i] = CRGB(GREEN);
            // }
            // FastLED.show();
            ledOn = !ledOn;
        }
    }
    if(flash == 2) {
        if(cubeTimer.timeHasPassed()){
            // for(int i = 1; i < leds[NUM_LEDS]; i++) {
            //     led[i] = CRGB(CYAN);
            // }
            // FastLED.show();
            ledOn = !ledOn;
        }
    }
}

// ============ algorithms ============


// ============ Slave Teensy ============
// void receive() {
//     if(Serial1.available() >= SLAVE_PACKET_SIZE) {
//         uint8_t firstByte = Serial1.read();
//         uint8_t secondByte = Serial1.peek();
//         if(firstByte == SLAVE_START_BYTE && secondByte == SLAVE_START_BYTE) {
//             uint8_t buffer[SLAVE_PACKET_SIZE - 2];
//             for(uint8_t i = 0; i < SLAVE_PACKET_SIZE - 2; i++) {
//                 buffer[i] = Serial1.read();
//             }
//             lrfs.value[4] = buffer[0] << 8 | buffer[1];
//             lrfs.value[5] = buffer[2] << 8 | buffer[3];
//             lrfs.value[6] = buffer[4] << 8 | buffer[5];
//             lrfs.value[7] = buffer[6] << 8 | buffer[7];
//             thermals.victim[2] = buffer[8] == 0 ? false : true;
//             thermals.victim[3] = buffer[9] == 0 ? false : true;
//         }
//     }
// }

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

// ============ Setup ============
void setup() {
    #if DEBUG
        Serial.begin(TEENSY_BAUD_RATE);
    #endif
    Serial1.begin(TEENSY_BAUD_RATE);
    lrfs.init();
    motors.init();
    imu.init();
    Serial.begin(TEENSY_BAUD_RATE);
    thermals.begin();
    thermals.setUnit(TEMP_C);
    pinMode(MASTER_LED, OUTPUT);
    digitalWrite(MASTER_LED, HIGH);
    digitalWrite(MASTER_LED, LOW);
}


void loop() {
    // ------------ updates ------------
    lrfs.update();
    light.update();
    debuger(1);
    masterFlash();
}