// ============ Includes ============
#include <LRFs.h>
#include <MotorController.h>
#include <Timer.h>
#include <LightSensor.h>
#include <i2c_t3.h>
#include <ThermalSensor_Bus1.h>
#include <ThermalSensor_Bus2.h>
#include <Adafruit_NeoPixel.h>

// ============ Setups ============
LRFs lrfs;
ThermalSensor_Bus1 thermFront;
ThermalSensor_Bus2 thermLeft;
MotorController motors;
LightSensor light;
Adafruit_NeoPixel strip(5, 23, NEO_GRB + NEO_KHZ800);
// ------------ Timers ------------
Timer ledTimer(MASTER_BLINK);
bool ledOn = false;
void masterFlash() {
    if(ledTimer.timeHasPassed()){
        digitalWrite(MASTER_LED, ledOn);
        ledOn = !ledOn;
    }
}

// ============ algorithms ============


// ============ Slave Teensy ============
void receive() {
    while(Serial1.available() >= SLAVE_PACKET_SIZE) {
        uint8_t firstByte = Serial1.read();
        uint8_t secondByte = Serial1.peek();
        if(firstByte == SLAVE_START_BYTE && secondByte == SLAVE_START_BYTE) {
            Serial1.read();
            uint8_t buffer[8];
            for(int i = 0; i < 8; i++) {
                buffer[i] = Serial1.read();
            }
            lrfs.value[4] = buffer[0] << 8 | buffer[1];
            lrfs.value[5] = buffer[2] << 8 | buffer[3];
            lrfs.value[6] = buffer[4] << 8 | buffer[5];
            lrfs.value[7] = buffer[6] << 8 | buffer[7];
        }
    }
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
// Thermal
void thermalPrint() {
    if(thermFront.read()) {
        Serial.println(String(thermFront.object(), 2));
    }
    if(thermLeft.read()) {
        Serial.println(String(thermLeft.object(), 2));
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
    if(debug == 3) {
        thermalPrint();
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
    light.init();
    motors.init();
    pinMode(MASTER_LED, OUTPUT);
    Serial.begin(9600);
    thermFront.begin();
    thermFront.setUnit(TEMP_C);
    thermLeft.begin();
    thermLeft.setUnit(TEMP_C);
    strip.begin();
    strip.clear();
    strip.show();
}


void loop() {
    // ------------ updates ------------
    receive();
    lrfs.update();
    light.update();
    debuger(3);
    masterFlash();
    thermFront.read();
    while(thermFront.object() <= 25) {
        debuger(3);
        thermFront.read();
        lrfs.update();
        while(lrfs.value[0] > 100) {
            thermFront.read();
            masterFlash();
            lrfs.update();
            debuger(3);
            motors.update(75, 75);
        }
        motors.update(-75, -75);
        delay(500);
        if(lrfs.value[2] > 150) {
            motors.update(-100, 100);
        }
        if(lrfs.value[3] > 150) {
            motors.update(100, -100);
        }
    }
    motors.update(0, 0);
    for(int i = 0; i < 5; i++) {
        strip.setPixelColor(i, strip.Color(225, 0, 0));
    }
    // strip.show();
    // delay(5000);
    // strip.clear();
    // strip.show();
}