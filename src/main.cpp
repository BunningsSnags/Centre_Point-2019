
// ============ Includes ============
#include <LRFs.h>
#include <Motors.h>
#include <Common.h>
#include <Timer.h>
#include <SparkFunMLX90614.h>

// ============ Setups ============
LRFs lrfs;
Motors motors;
IRTherm temp;
    // ------------ Timers ------------
Timer cubeTimer(80000);
Timer turnTimer(1000000);
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
    temp.begin();
    temp.setUnit(TEMP_F);
}

// ============ Main ============
void loop() {
    // ------------ Debuging ------------
    // while(true){
    //     printer();
    //     flash();
    // }
    Serial.print("I am before read");
    if (temp.read()) {
        Serial.print("I Have Read");
        float ambientT = temp.ambient(); // Get updated ambient temperature
        float objectT = temp.object(); // Get updated object temperature
        Serial.println("Ambient: " + String(ambientT));
        Serial.println("Object: " + String(objectT));
        Serial.println();
    }
    motors.update(-50, 50);
}
