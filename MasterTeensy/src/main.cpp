#include <Logic.h>
Logic logs;
Adafruit_NeoPixel strip(NUM_RGB_LEDS, RGB_PIN, NEO_GRB + NEO_KHZ800);


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
            logs.lrfs.value[4] = buffer[0] << 8 | buffer[1];
            logs.lrfs.value[5] = buffer[2] << 8 | buffer[3];
            logs.lrfs.value[6] = buffer[4] << 8 | buffer[5];
            logs.lrfs.value[7] = buffer[6] << 8 | buffer[7];
        }
    }
}

// ============ Debugers ==========````````````````````````````````````````````````````````````````````````````````````````
void lrfsPrint() {
    for(int i = 0; i < LRF_NUM; i++) {
        Serial.print(logs.lrfs.value[i]);
        Serial.print("\t");
    }
    Serial.println("Front-Left, Front-Right, Left-Front, Right-Front, Left-Back, Right-Back, Back-Left, Back-Right");
}
void lightPrint() {
    for(int i = 0; i < LIGHTSENSOR_NUM; i++) {
        Serial.print(logs.light.light[i]);
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
  Serial.print(logs.imu.horizontalHeading);
  Serial.print("\t");
  Serial.print(logs.imu.verticalHeading);
  Serial.print("\t");
  Serial.println("Horizontal, Vertical");
}
void correctionPrint() {
  Serial.print(logs.IMUCorrection);
  Serial.print("\t");
  Serial.print(logs.LRFCorrection);
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

void tileCheck() {
  logs.curTile = logs.lrfs.checkTile(logs.curTile, logs.imu.horizontalHeading);
  // curTile = light.spotBlack(600, curTile);
  // curTile = light.spotSilver(200, curTile);
}

// ============ Setup ============
void setup() {
  #if DEBUG
      Serial.begin(TEENSY_BAUD_RATE);
  #endif
  Serial1.begin(TEENSY_BAUD_RATE);
  logs.lrfs.init();
  logs.light.init();
  logs.motors.init();
  pinMode(MASTER_LED, OUTPUT);
  Serial.begin(9600);
  logs.imu.init();
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.setBrightness(20);
  strip.show();
}

void update() {
  masterFlash();
  receive();
  logs.update();
}

void loop() {
  // debug(dLight);
  update();
  
  //! ---------------- Navigation ----------------
  logs.Navigate();
}