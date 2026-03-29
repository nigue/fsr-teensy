#pragma once

#include <stddef.h>
#include <stdint.h>

// ─────────────────────────────
// Abstracción
// ─────────────────────────────
class EepromStorage {
public:
  virtual ~EepromStorage() {}

  virtual uint8_t readByte(size_t address) const = 0;
  virtual void writeByte(size_t address, uint8_t value) = 0;
};

// ─────────────────────────────
// Implementación Arduino
// ─────────────────────────────
class ArduinoEepromStorage : public EepromStorage {
public:
  uint8_t readByte(size_t address) const override;
  void writeByte(size_t address, uint8_t value) override;
};
