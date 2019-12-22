import sensor, image
from pyb import UART, LED


while true:
    centreX = 120
    centreY = 120
    redTHRESHOLD = [(57, 77, 18, 70, -10, 61)]
    vWin = (0,0,240,240)

    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.skip_frames(time = 2000)
    sensor.set_windowing(vWin)

    sensor.set_saturation(3)
    sensor.set_contrast(3)
    sensor.set_brightness(-1)

    uart = UART(3, 9600, timeout_char = 1000)

    def BiggestBlob(bBlob):
        if not bBlob:
            return None
        maxBlob = bBlob[0]
        for blob in bBlob:
            if blob.area() > maxBlob.area():
                maxBlob = blob
        return maxBlob

    def send(output):
        uart.writechar(255)
        for i in output:
            uart.writechar(i)
            print(i)

    while(True):
        outBuffer = [0,0]
        img = sensor.snapshot()
        redColour = BiggestBlob(img.find_blobs(redTHRESHOLD))

        if redColour:
            outBuffer[0] = redColour.cx()
            outBuffer[1] = redColour.cy()

        send(outBuffer)

        if redColour:
            img.draw_rectangle(redColour.rect())
