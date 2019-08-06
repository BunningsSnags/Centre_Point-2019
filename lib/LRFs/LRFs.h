#ifndef LRFS_H_
#define LRFS_H_

#include <Common.h>

class LRFs {
public:
    LRFs() {}
    void init();
    void update();
    void print();
private:
    int num = 0;

}

#endif