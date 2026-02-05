#pragma once

#include <EEPROM.h>

#include "../repository/EepromStorage.h"

class ArduinoEepromStorage : public EepromStorage {
 public:
  uint8_t readByte(size_t address) const override {
    return EEPROM.read(address);
  }

  void writeByte(size_t address, uint8_t value) override {
    EEPROM.write(address, value);
  }
};
