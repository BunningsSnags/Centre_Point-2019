// ============ Includes ============
#include <LRFs.h>
#include <Motors.h>
#include <Common.h>
#include <Timer.h>

// ============ Setups ============
LRFs lrfs;
Motors motors;

    // ------------ Timers ------------
Timer RGBTimer(800000);
Timer LEDTimer(800000);
bool ledOn = false;

    // ------------ LED Flash ------------
void flash(){
    if(LEDTimer.timeHasPassed()){
        digitalWrite(ledPin, ledOn);
        ledOn = !ledOn;
    }

}

    // ------------ LRF Print ------------
void printer(){
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(lrfs.value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, Front-Right, Left-Left, Left-Right, Back-Left, Back-Right, Right-Left, Right-Right");
}
    // ------------ Normal Setup ------------
void setup() {
    lrfs.init();
    motors.init();
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin, LOW);
}

// ============ Main ============
void loop() {
    // ------------ Debuging ------------
    while(true){
        printer();
        flash();
    }
    motors.update(-50, 50);




}
