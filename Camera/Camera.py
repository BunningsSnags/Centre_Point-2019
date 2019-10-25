import sensor, image
from pyb import UART, LED

centreX = 120
centreY = 120
redTHRESHOLD = [(57, 77, 18, 70, -10, 61)]
vWin = (0,0,120,120)

DEBUGGING = True


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time = 2000)
sensor.set_windowing(vWin)

sensor.set_saturation(3)
sensor.set_contrast(3)
sensor.set_brightness(-1)

uart = UART(3, 9600, timeout_char = 10)

def BiggestBlob(bBlob):
    if not bBlob:
        return None
    maxBlob = bBlob[0]
    for blob in bBlob:
        if blob.area() > maxBlob.area():
            maxBlob = blob
    return maxBlob

def getDistance(blob):
    x = blob.cx() - centreX
    y = blob.cy() - centreY
    return int(sqrt(x**2 + y**2))


def send(output=254):
    uart.writechar(255)
    uart.writechar(output)

while(True):
    img = sensor.snapshot()

    redBlob = BiggestBlob(img.find_blobs(redTHRESHOLD, x_stride=2, y_stride=2, merge=True, margin=10))

    if redBlob:
        dist = getDistance(redBlob)
        send(dist)

    if DEBUGGING:
        img.draw_cross(centreX, centreY)
        if redBlob:
            img.draw_rectangle(redBlob.rect())
            print(dist)
