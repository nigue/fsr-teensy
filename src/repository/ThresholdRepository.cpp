#include "ThresholdRepository.h"
#include "../eeprom/EepromLayout.h"

ThresholdRepository::ThresholdRepository(EepromStorage& repository)
  : repository_(repository) {
}

void ThresholdRepository::save(const Threshold& threshold) {
  uint8_t index = threshold.getSensorIndex();
  if (index >= EepromLayout::THRESHOLD_COUNT) return;

  repository_.writeByte(
    EepromLayout::thresholdAddr(index),
    threshold.getValue()
  );
}

Threshold ThresholdRepository::load(uint8_t index) const {
  if (index >= EepromLayout::THRESHOLD_COUNT) {
    return Threshold(index, 0);
  }

  int16_t value = repository_.readByte(EepromLayout::thresholdAddr(index));

  return Threshold(index, value);
}
