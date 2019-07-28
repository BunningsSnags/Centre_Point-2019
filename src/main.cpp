// ============ Includes ============
#include <LRFs.h>
#include <Motors.h>
#include <Common.h>
#include <Timer.h>
#include <ThermalSensors.h>

// ============ Setups ============
LRFs lrfs;
Motors motors;
IRTherm temp;
    // ------------ Timers ------------
Timer cubeTimer(80000);
Timer turnTimer(1000000);
Timer LEDTimer(800000);
bool ledOn = false;

    //  ------------ Temp Recordings  ------------
void tempRead() {
    if (temp.read()) {
        float ambientT = temp.ambient();
        float objectT = temp.object();
        Serial.println("Ambient: " + String(ambientT));
        Serial.println("Object: " + String(objectT));
        Serial.println();
    }
}
    // ------------ LED Flash ------------
void flash() {
    if(LEDTimer.timeHasPassed()){
        digitalWrite(ledPin, ledOn);
        ledOn = !ledOn;
    }

}
    // ------------ LRF Print ------------
void lrfRead(){
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
    temp.setUnit(TEMP_C);
}

// ============ Main ============
void loop() {
    //------------ Debuging ------------
    while(true){
        flash();
        tempRead();
        //lrfRead();
    }
//     while(lrfs.value[0] && lrfs.value[1] > 300){
//     // ----------- Random left turn -----------
//     if(lrfs.value[2] > 150 && lrfs.value[3] > 150){
//       motors.update(80, 80);
//       delay(700);
//       if(lrfs.value[3] != ((lrfs.value[4] - 5) < lrfs.value[4] < (lrfs.value[4] + 5))){
//         motors.update(-80, 80);
//       }
//     }
//     motors.update(80, 80);
//     // ----------- Black Square -----------
//     if(analogRead(frontLight) || analogRead(backLight) < 70){
//       // Left escape
//       if(lrfs.value[2] && lrfs.value[3] > 250){
//         motors.update(80, -80);
//         delay(1000);
//           // turn until straight
//         while(lrfs.value[4] != lrfs.value[5]){
//           motors.update(80, -80);
//         }
//       }
//       // Right escape
//       if(lrfs.value[6] && lrfs.value[7] > 250){
//         motors.update(-80, 80);
//         delay(1000);
//           // turn until straight
//         while(lrfs.value[4] != lrfs.value[5]){
//           motors.update(-80, 80);
//         }
//       }
//       // No turns out of black square
//       else{
//         motors.update(-80, 80);
//         delay(1000);
//           // Turn until sideways
//         while(lrfs.value[4] != lrfs.value[5]){
//           motors.update(-80, 80);
//         }
//         // Second turn around for full 180
//         motors.update(-80, 80);
//         delay(1000);
//           // turn until straight again
//         while(lrfs.value[4] != lrfs.value[5]){
//           motors.update(-80, 80);
//         }
//       }
//     }
//   }
// // ============ Turn visable ============
//   // ----------- Robot is straight -----------
//   while(lrfs.value[0] > 150 && lrfs.value[1] > 150){
//     motors.update(80, 80);
//       // turn left
//     if(250 < lrfs.value[2] > 255 && 250 < lrfs.value[3] < 255){
//       motors.update(80, -80);
//       delay(1000);                      /* This is just to make it turn a tinny bit first so sensors arent already equal */
//         // turn until straight
//       while(lrfs.value[4] != lrfs.value[5]){
//         motors.update(60, -60);
//       }
//     }
//   }
//     // turn right
//   if(250 < lrfs.value[6] > 255 && 250 < lrfs.value[7] < 255){
//     motors.update(-80, 80);
//     delay(1000);                     /* This is just to make it turn a tinny bit first so sensors arent already equal */
//       // turn until straight
//     while(lrfs.value[4] != lrfs.value[5]){
//       motors.update(-60, 60);
//     }
//   }
}
