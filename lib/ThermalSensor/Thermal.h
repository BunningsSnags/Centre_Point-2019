#include <i2c_t3.h>
#include "Common.h"


class Thermal  {
 public:
  Thermal(uint8_t dr = MLX90614_I2CADDR);
  void init();
  uint32_t readID(void);

  double readObjectTempC(void);
  double readAmbientTempC(void);
  double readObjectTempF(void);
  double readAmbientTempF(void);

 private:
  float readTemp(uint8_t reg);

  uint8_t _addr;
  uint16_t read16(uint8_t addr);
  void write16(uint8_t addr, uint16_t data);
};