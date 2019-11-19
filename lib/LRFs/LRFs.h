#ifndef LRFS_H_
#define LRFS_H_

#include <Common.h>

class LRFs {
public:
    LRFs() {}
    void init();
    void update();
    uint16_t wallAverage(int lrf1, int lrf2, double header);
    uint16_t average(int lrf1, int lrf2);
    uint16_t value[LRF_NUM] = {0};
    Tile checkTile(Tile tile, double heading);
    int tileDist(double heading);
private:
    uint16_t averaged = 0;
};

#endif