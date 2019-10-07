#include "Thermal.h"

Thermal::Thermal(uint8_t i2caddr) {
  _addr = i2caddr;
}


void Thermal::init(void) {
  // Wire.begin(I2C_MASTER, 0x00, 19, 18);
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  // Wire2.begin(I2C_MASTER, 0x00, I2C_PINS_3_4, I2C_PULLUP_INT, 400000);

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

  Wire.beginTransmission(_addr); // start transmission to device 
  Wire.write(a); // sends register address to read from
  Wire.endTransmission(false); // end transmission
  
  Wire.requestFrom(_addr, (uint8_t)3);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  ret |= Wire.read() << 8; // receive DATA

  uint8_t pec = Wire.read();

  return ret;
}