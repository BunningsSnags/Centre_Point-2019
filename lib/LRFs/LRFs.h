#ifndef LRFS_H
#define LRFS_H

#include <Common.h>

class LRFs {
public:
    LRFs() {};
    void init();
    void print();
    void update();
    uint16_t value[LRF_NUM] = {0};
private:
    uint8_t lrf1 = 0;
    uint8_t lrf2 = 0;
};



#endif