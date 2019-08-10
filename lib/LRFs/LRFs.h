#ifndef LRFS_H_
#define LRFS_H_

#include <Common.h>

class LRFs {
public:
    LRFs() {}
    void init();
    void update();
    void average(uint16_t lrf1, uint16_t lrf2);
    uint16_t value[LRF_NUM] = {0};
private:
    uint16_t averaged = 0;
};

#endif