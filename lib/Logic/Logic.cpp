/* This is the logic file where the functions for main.cpp are made
-------------------------------------------------------------------

Navigate is used to move around the maze
Record is used to collect the details about the tile and add it to the array
update is used to update all libraries

lrfInput is used to collect a certain value

-------------------------------------------------------------------
*/

// ============ updates ============
void Logic::update() {
  logic.imu.update();
  logic.light.update();
  logic.lrfs.update();
  masterFlash();
  receive();
  IMUCorrection = round(logic.IMUPID.update(logic.imu.horizontalHeading, direction, 0));
  LRFCorrection = constrain(round(logic.LRFPID.update(lrfInput(), 0, 0)), -300, 300);
}

int Logic::lrfInput() {
  int leftSide = logic.lrfs.wallAverage(2, 4, logic.imu.horizontalHeading);
  int rightSide = logic.lrfs.wallAverage(3, 5, logic.imu.horizontalHeading);
  int16_t input = leftSide-rightSide;
  return input;
}



// -------------------------------------- Main -----------------------------------------

void Logic::Navigate() {
    // ------------ Navigate ------------
  // if(!therm.spotHeat(30)) {
    if(lrfs.average(0, 1) > 100) {
      motors.update(150, 150, IMUCorrection);
      // colorWipe(strip.Color(BLUE), 1);

      // light sensors
      if(light.light[1] > 600) {
        // staaaapp, and go back
        motors.update(0, 0, IMUCorrection);
        motors.update(-100, -100, IMUCorrection);
        delay(1000);

        // Check turn and Turn
        if(lrfs.average(2, 4) > lrfs.average(3, 5)) {
          direction = mod(direction + 90, 360);
          IMUCorrection = round(IMUPID.update(imu.horizontalHeading, direction, 0));
          while(!motors.setOrientation(IMUCorrection)) {
            update();
          }
        }
        else if(lrfs.average(3, 5) > lrfs.average(2, 4)) {
          direction = mod(direction - 90, 360);
          IMUCorrection = round(IMUPID.update(imu.horizontalHeading, direction, 0));
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
  //   update();
  //   motors.update(0, 0, IMUCorrection);
  //   colorWipe(strip.Color(GREEN), 1);
  //   delay(100);
  //   colorWipe(strip.Color(0, 0, 0), 1);
  //   delay(100);
  //   colorWipe(strip.Color(GREEN), 1);
  //   delay(100);
  //   colorWipe(strip.Color(0, 0, 0), 1);
  //   delay(100);
  //   colorWipe(strip.Color(GREEN), 1);
  //   delay(100);
  //   colorWipe(strip.Color(0, 0, 0), 1);
  //   delay(100);
  //   !therm.spotHeat(30);
  //   therm.value[0] = 0;
  // }
}

void Logic::Record() {

}