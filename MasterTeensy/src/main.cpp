// ============ Includes ============
#include <LRFs.h>
#include <MotorController.h>
#include <Timer.h>
#include <LightSensor.h>
#include <SPI.h>
#include <FastLED.h>
#include <MPU.h>
#include <PID.h>
#include <Tile.h>
#include <Camera.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// ============ Setups ============
LRFs lrfs;
MotorController motors;
LightSensor light;
MPU imu;
PID IMUPID = PID(10, 0, 0, 255*2);
PID LRFPID = PID(1, 0, -1.5, 255*2);
Tile curTile;
Camera cam;
double IMUCorrection;
double LRFCorrection;
double direction = 0;
int objDirection = 0;

// ------------ Timers ------------
Timer ledTimer(MASTER_BLINK);
bool ledOn = true;
void masterFlash() {
    if(ledTimer.timeHasPassed()){
        digitalWrite(MASTER_LED, ledOn);
        ledOn = !ledOn;
    }
}

Timer rgbTimer(250);
bool flash = false;
int flashCounter = 0;
// void rgbFlash() {
//   if(flashCounter < 4) {
//       if(rgbTimer.timeHasPassed()){
//     rgbTimer.resetTime();
//     if(flash) {
//       colorWipe(strip.Color(0,0,0), 1);
//     } else {
//       colorWipe(strip.Color(GREEN), 1);
//       flashCounter++;
//     }
//     flash = !flash;
//   } 
//   } else {
//     colorWipe(strip.Color(0,0,0), 1);
//   }
// }

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

int lrfInput() {
  int leftSide = lrfs.wallAverage(2, 4, imu.horizontalHeading);
  int rightSide = lrfs.wallAverage(3, 5, imu.horizontalHeading);
  int16_t input = leftSide-rightSide;
  return input;
}

// ============ Debugers ==========````````````````````````````````````````````````````````````````````````````````````````
void lrfsPrint() {
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(lrfs.value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, Front-Right, Left-Front, Right-Front, Left-Back, Right-Back, Back-Left, Back-Right");
}
void lightPrint() {
    for(int i = 0; i < LIGHTSENSOR_NUM; i++) {
        Serial.print(light.light[i]);
        Serial.print("\n");
    }
    Serial.println("Front1, Front2, Back");
}
void thermalPrint() {
  // for(int i = 0; i < 4; i++) {
        // Serial.print(therm.value[i]);
        // Serial.print("\t");
    // }
    // Serial.printf("Front, Left, Right, Back, Spotted: %d\n", therm.spotHeat(30));
}
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
void wallPrint() {
  Serial.print(lrfInput());
  Serial.print("\t");
  Serial.println("input");
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
  if(sensor == 6) {
    wallPrint();
  }
}

// ============ updates ============
void update() {
  imu.update();
  light.update();
  lrfs.update();
  masterFlash();
  // rgbFlash();
  receive();
  IMUCorrection = -round(IMUPID.update(imu.horizontalHeading, direction, 0));
  LRFCorrection = constrain(round(LRFPID.update(lrfInput(), 0, 0)), -300, 300);
}

void tileCheck() {
  curTile = lrfs.checkTile(curTile, imu.horizontalHeading);
  // curTile = light.spotBlack(600, curTile);
  // curTile = light.spotSilver(200, curTile);
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
  pinMode(MASTER_LED, OUTPUT);
  Serial.begin(9600);
  imu.init();
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  cam.init();
  // imu.verticalHeading = 2;
}

void loop() {
  update();
  // debug(dLrfs);

  Serial.println(lrfs.tileDist(imu.horizontalHeading));
  if(lrfs.wallAverage(6, 7, imu.horizontalHeading) < (lrfs.tileDist(imu.horizontalHeading)+300)) {
    motors.update(100, 100, IMUCorrection);
  }
  else {
    motors.update(0, 0, IMUCorrection);
  }

  //* ------------ Navigate ------------
  // if(!cam.isThere(20)) {
    if(lrfs.average(0, 1) > 100) {
      motors.update(SPEED, SPEED, IMUCorrection);
      // colorWipe(strip.Color(BLUE), 1);     

      // light sensors
      if(light.spotBlack(500)) {
        // staaaapp, and go back
        motors.update(0, 0, IMUCorrection);
        motors.update(-SPEED, -SPEED, IMUCorrection);
        delay(2000);

        // Check turn and Turn
        if(lrfs.average(2, 4) > lrfs.average(3, 5)) {
          direction = mod(direction + 90, 360);
          IMUCorrection = round(IMUPID.update(imu.horizontalHeading, direction, 360));
          while(!motors.setOrientation(IMUCorrection)) {
            update();
          }
        }
        else if(lrfs.average(3, 5) > lrfs.average(2, 4)) {
          direction = mod(direction - 90, 360);
          IMUCorrection = round(IMUPID.update(imu.horizontalHeading, direction, 360));
          while(!motors.setOrientation(IMUCorrection)) {
            update();
          }
        }
      }
    }
    // normal turn
    else {
      if(lrfs.average(2, 4) > lrfs.average(3, 5)) {
        // colorWipe(strip.Color(RED), 1);
        direction = mod(direction + 90, 360);
        IMUCorrection = round(IMUPID.update(imu.horizontalHeading, direction, 0));
        while(!motors.setOrientation(IMUCorrection)) {
          update();
          }
        }
        else if(lrfs.average(3, 5) > lrfs.average(2, 4)) {
          // colorWipe(strip.Color(GREEN), 1);
          direction = mod(direction - 90, 360);
          IMUCorrection = round(IMUPID.update(imu.horizontalHeading, direction, 0));
          while(!motors.setOrientation(IMUCorrection)) {
            update();
        }
      }
    }
  // else {
  // motors.update(0, 0, IMUCorrection);
  // flashCounter = -2;
  // isThere(20) = false;

  // ** Try and get the navigation functions made
  /**
   *? checkTile() is when all things on the tile are recorded including walls
   *? pathFind() the robot will choose a direction depending on the checkTile answers and set an endpoint
   *? Navigate(pathFind) will simply navigate to wherever the endpoint is set at
   *? avoidTile() means that it will first avoid the tile and then tell the checkTile function if its a black tile or ramp
  */
  /** 
   * ! checkTile();
   * ! if(victim) {
   * !   victimSave();
   * ! }
   * ! pathFind();
   * ! if(!blackTile) {
   * !    if(!ramp) {
   * !      Navigate(pathFind);
   * !    }
   * !    else {
   * !      avoidTile(ramp);
   * !    }
   * !  }
   * ! else {
   * !  avoidTile(blackTile);
   * ! }
  */
}