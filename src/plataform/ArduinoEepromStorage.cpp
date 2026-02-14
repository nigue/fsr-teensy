#include <EEPROM.h>
#include "ArduinoEepromStorage.h"

uint8_t ArduinoEepromStorage::readByte(size_t address) const {
  return EEPROM.read(address);
}

void ArduinoEepromStorage::writeByte(size_t address, uint8_t value) {
  EEPROM.write(address, value);
}