#include <Camera.h>

void Camera::init() {
    camSerial.begin(CAM_BAUD);
}

int Camera::read() {
    if(camSerial.available() >= CAM_PACKET_SIZE) {
        if(camSerial.read() == CAM_START_BYTE) {
            uint8_t camBuffer[CAM_PACKET_SIZE - 1];

            for(int i = 0; i < CAM_PACKET_SIZE - 1; i++) {
                camBuffer[i] = camSerial.read();
            }

            redDistance = camBuffer[0];

        }
    }
    return redDistance;
}

bool Camera::isThere(int distance) {
    return read() < distance;
}