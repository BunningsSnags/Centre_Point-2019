#ifndef LRFS_H
#define LRFS_H

#include <Common.h>
#include <SoftwareSerial.h>

class LRFs {
public:
    LRFs() {};
    void init();
    void update();
    uint16_t value[LRF_NUM] = {0};
private:
    SoftwareSerial lrfRight1 = SoftwareSerial(27, 26);
    SoftwareSerial lrfBack1 = SoftwareSerial(25, 24);
    SoftwareSerial lrfBack2 = SoftwareSerial(11, 12);
};


#endif