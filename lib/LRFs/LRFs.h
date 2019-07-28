#ifndef LRFS_H
#define LRFS_H

#include <Common.h>

class LRFs {
public:
    LRFs() {};
    void init();
    void update();
    uint16_t value[LRF_NUM] = {0};
};


#endif