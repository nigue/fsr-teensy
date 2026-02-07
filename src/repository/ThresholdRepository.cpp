#include "ThresholdRepository.h"

#include <EEPROM.h>

namespace {
class ArduinoEepromStorageAdapter : public EepromStorage {
 public:
  uint8_t readByte(size_t address) const override {
    return EEPROM.read(address);
  }

  void writeByte(size_t address, uint8_t value) override {
    EEPROM.write(address, value);
  }
};

ArduinoEepromStorageAdapter storage;

void writeInt16(EepromStorage& storageRef, size_t address, int16_t value) {
  storageRef.writeByte(address, static_cast<uint8_t>(value & 0xFF));
  storageRef.writeByte(address + 1, static_cast<uint8_t>((value >> 8) & 0xFF));
}

int16_t readInt16(const EepromStorage& storageRef, size_t address) {
  uint8_t low = storageRef.readByte(address);
  uint8_t high = storageRef.readByte(address + 1);
  return static_cast<int16_t>((static_cast<int16_t>(high) << 8) | low);
}
}  // namespace

void ThresholdRepository::save(const Threshold& threshold) {
  uint8_t index = threshold.getSensorIndex();
  if (index >= EepromLayout::THRESHOLD_COUNT) {
    return;
  }

  writeInt16(storage, EepromLayout::thresholdAddr(index), threshold.getValue());
}

Threshold ThresholdRepository::load(uint8_t index) {
  if (index >= EepromLayout::THRESHOLD_COUNT) {
    return Threshold(index, 0);
  }

  int16_t value = readInt16(storage, EepromLayout::thresholdAddr(index));
  return Threshold(index, value);
}
