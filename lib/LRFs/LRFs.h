#ifndef LRFS_H_
#define LRFS_H_

#include <Common.h>

class LRFs {
public:
    LRFs() {}
    void init();
    void update();
    uint16_t value[LRF_NUM] = {0};
};

#endif