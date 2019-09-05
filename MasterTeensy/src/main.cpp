// ============ Includes ============
#include <LRFs.h>
#include <MotorController.h>
#include <Timer.h>
#include <LightSensor.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <MPU.h>
#include <PID.h>
#include <ThermalSensor.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// ============ Setups ============
LRFs lrfs;
MotorController motors;
LightSensor light;
MPU imu;
PID IMUPID = PID(10, 0, 0, 255);
PID LRFPID = PID(10, 0, 0, 255);
ThermalSensor therm;
Adafruit_NeoPixel strip(NUM_RGB_LEDS, RGB_PIN, NEO_GRB + NEO_KHZ800);
// Corrections
double IMUCorrection;
double LRFCorrection;
double direction = 0;

// ------------ Timers ------------
Timer ledTimer(MASTER_BLINK);
bool ledOn = true;
void masterFlash() {
    if(ledTimer.timeHasPassed()){
        digitalWrite(MASTER_LED, ledOn);
        ledOn = !ledOn;
    }
}

// ============ Slave Teensy ============
void receive() {
    while(Serial1.available() >= SLAVE_PACKET_SIZE) {
        uint8_t firstByte = Serial1.read();
        uint8_t secondByte = Serial1.peek();
        if(firstByte == SLAVE_START_BYTE && secondByte == SLAVE_START_BYTE) {
            Serial1.read();
            uint8_t buffer[8];
            for(int i = 0; i < 8; i++) {
                buffer[i] = Serial1.read();
            }
            lrfs.value[4] = buffer[0] << 8 | buffer[1];
            lrfs.value[5] = buffer[2] << 8 | buffer[3];
            lrfs.value[6] = buffer[4] << 8 | buffer[5];
            lrfs.value[7] = buffer[6] << 8 | buffer[7];
        }
    }
}

// ============ Debugers ============
// LRF
void lrfsPrint() {
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(lrfs.value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, Front-Right, Left-Front, Right-Front, Left-Back, Right-Back, Back-Left, Back-Right");
}
// Light Sensor
void lightPrint() {
    for(int i = 0; i < LIGHTSENSOR_NUM; i++) {
        Serial.println(light.light[i]);
    }
}
// Thermal
void thermalPrint() {
}
// IMU
void imuPrint() {
  Serial.print(imu.horizontalHeading);
  Serial.print("\t");
  Serial.print(imu.verticalHeading);
  Serial.print("\t");
  Serial.println("Horizontal, Vertical");
}
void correctionPrint() {
  Serial.print(IMUCorrection);
  Serial.print("\t");
  Serial.print(LRFCorrection);
  Serial.print("\t");
  Serial.println("IMU, LRF");
}
// Debuging function
void debug(int sensor) {
  if(sensor == 1) {
    lrfsPrint();
  }
  if(sensor == 2) {
    lightPrint();
  }
  if(sensor == 3) {
    thermalPrint();
  }
  if(sensor == 4) {
    imuPrint();
  }
  if(sensor == 5) {
    correctionPrint();
  }
}

int lrfSetPoint() {
  int centre = 0;
  centre = (lrfs.average(2, 4) + lrfs.average(3, 5))/2;
  return centre;
}

int lrfInput() {
  int leftSide = lrfs.average(2, 4);
  int rightSide = lrfs.average(3, 5);
  int input = leftSide-rightSide;
  return input;
}

// Lights
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// ============ updates ============
void update() {
  imu.update();
  light.update()
  lrfs.update();
  therm.update();
  masterFlash();
  receive();
  IMUCorrection = round(IMUPID.update(imu.horizontalHeading, direction, 0));
  LRFCorrection = round(LRFPID.update(lrfInput(), lrfSetPoint(), 0));
}

// ============ Setup ============
void setup() {
  #if DEBUG
      Serial.begin(TEENSY_BAUD_RATE);
  #endif
  Serial1.begin(TEENSY_BAUD_RATE);
  lrfs.init();
  light.init();
  motors.init();
  therm.init();
  pinMode(MASTER_LED, OUTPUT);
  Serial.begin(9600);
  imu.init();
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.setBrightness(20);
  strip.show();
}


void loop() {
  update();
  // debug(1);

  // ------------ Main ------------
  // if(therm.victim[i] <= 20)) {
    if(lrfs.average(0, 1) > 100) {
      motors.update(100, 100, LRFCorrection);
    }
    else {
      direction = mod(direction + 90, 360);
      IMUCorrection = round(IMUPID.update(imu.horizontalHeading, direction, 0));
      while(!motors.setOrientation(IMUCorrection)) {
        update();
      }
    }
  // }
  // motors.update(0, 0, LRFCorrection);
  // colorWipe(strip.Color(GREEN), 1);
  // delay(500);
  // colorWipe(strip.Color(GREEN), 1);
  // delay(500);
  // colorWipe(strip.Color(GREEN), 1);
  // delay(500);
  // //Figure out how to stop it from seeing the heat pad now
}