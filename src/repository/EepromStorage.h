#pragma once

#include <stddef.h>
#include <stdint.h>

class EepromStorage {
 public:
  virtual ~EepromStorage() {}

  virtual uint8_t readByte(size_t address) const = 0;
  virtual void writeByte(size_t address, uint8_t value) = 0;
};
