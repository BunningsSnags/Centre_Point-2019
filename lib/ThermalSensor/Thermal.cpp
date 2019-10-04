#include "Thermal.h"

Thermal::Thermal(uint8_t i2caddr) {
  _addr = i2caddr;
}


boolean Thermal::begin(void) {
  // Wire1.begin(I2C_MASTER, 0x00, 37, 38);
  Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_37_38, I2C_PULLUP_INT, 400000);
  // Wire2.begin(I2C_MASTER, 0x00, I2C_PINS_3_4, I2C_PULLUP_INT, 400000);

  /*
  for (uint8_t i=0; i<0x20; i++) {
    Serial.print(i); Serial.print(" = ");
    Serial.println(read16(i), HEX);
  }
  */
  return true;
}

//////////////////////////////////////////////////////


double Thermal::readObjectTempF(void) {
  return (readTemp(MLX90614_TOBJ1) * 9 / 5) + 32;
}


double Thermal::readAmbientTempF(void) {
  return (readTemp(MLX90614_TA) * 9 / 5) + 32;
}

double Thermal::readObjectTempC(void) {
  return readTemp(MLX90614_TOBJ1);
}


double Thermal::readAmbientTempC(void) {
  return readTemp(MLX90614_TA);
}

float Thermal::readTemp(uint8_t reg) {
  float temp;
  
  temp = read16(reg);
  // Serial.printf("temp raw: %f\n", temp);
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

/*********************************************************************/

uint16_t Thermal::read16(uint8_t a) {
  uint16_t ret;

  Wire1.beginTransmission(_addr); // start transmission to device 
  Wire1.write(a); // sends register address to read from
  Wire1.endTransmission(false); // end transmission
  
  Wire1.requestFrom(_addr, (uint8_t)3);// send data n-bytes read
  ret = Wire1.read(); // receive DATA
  ret |= Wire1.read() << 8; // receive DATA

  uint8_t pec = Wire1.read();

  return ret;
}