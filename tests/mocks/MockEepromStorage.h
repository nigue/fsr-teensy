#pragma once
#include "../../src/plataform/ArduinoEepromStorage.h"
#include <map>

class MockEepromStorage : public EepromStorage {
public:
  std::map<size_t, uint8_t> memory;

  uint8_t readByte(size_t addr) const override {
    auto it = memory.find(addr);
    return (it != memory.end()) ? it->second : 0xFF;
  }

  void writeByte(size_t addr, uint8_t value) override {
    memory[addr] = value;
  }
};
