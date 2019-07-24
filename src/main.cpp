#include <LRFs.h>
#include <Motors.h>

LRFs lrfs;
Motors motors;

void setup() {
    lrfs.init();
    motors.init();
}

void loop() {
    lrfs.update();
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(lrfs.value[i]);
        Serial.print("\t");
    }
    Serial.println();
    motors.update(100, 100);
}
