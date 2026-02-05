#include "ThresholdRepository.h"

ThresholdRepository::ThresholdRepository(EepromStorage& storage)
    : storage_(storage) {}

Threshold ThresholdRepository::load(uint8_t sensorIndex) const {
  if (sensorIndex >= EepromLayout::THRESHOLD_COUNT) {
    return Threshold(sensorIndex, EepromLayout::DEFAULT_THRESHOLD);
  }

  uint8_t low = storage_.readByte(EepromLayout::thresholdLowAddr(sensorIndex));
  uint8_t high = storage_.readByte(EepromLayout::thresholdHighAddr(sensorIndex));

  int16_t value = static_cast<int16_t>((high << 8) | low);

  if (value < 0 || value > 1023) {
    value = EepromLayout::DEFAULT_THRESHOLD;
  }

  return Threshold(sensorIndex, value);
}

void ThresholdRepository::save(const Threshold& threshold) {
  uint8_t sensorIndex = threshold.getSensorIndex();

  if (sensorIndex >= EepromLayout::THRESHOLD_COUNT) {
    return;
  }

  int16_t value = threshold.getValue();
  uint8_t low = static_cast<uint8_t>(value & 0xFF);
  uint8_t high = static_cast<uint8_t>((value >> 8) & 0xFF);

  storage_.writeByte(EepromLayout::thresholdLowAddr(sensorIndex), low);
  storage_.writeByte(EepromLayout::thresholdHighAddr(sensorIndex), high);
}
