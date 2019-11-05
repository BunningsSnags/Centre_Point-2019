#ifndef CAMERA_H_
#define CAMERA_H_

#include <Common.h>

class Camera {
public:
    Camera() {}
    void init();
    int read();
    bool isThere(int distance);
private:
    int redDistance;
};

#endif