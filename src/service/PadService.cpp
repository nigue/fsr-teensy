#include "PadService.h"

PadService::PadService(ThresholdRepository& thresholdRepository,
                       PadConfigRepository& configRepository)
    : thresholdRepository_(thresholdRepository),
      configRepository_(configRepository),
      side_(PadSide::LEFT) {
  for (uint8_t i = 0; i < EepromLayout::THRESHOLD_COUNT; ++i) {
    thresholds_[i] = EepromLayout::DEFAULT_THRESHOLD;
    currentValues_[i] = 0;
    offsets_[i] = 0;
  }
}

void PadService::initialize() {
  configRepository_.initializeMagic();
  side_ = configRepository_.loadSide();

  for (uint8_t i = 0; i < EepromLayout::THRESHOLD_COUNT; ++i) {
    thresholds_[i] = thresholdRepository_.load(i).getValue();
  }
}

PadSide PadService::getPadSide() const {
  return side_;
}

void PadService::setPadSide(PadSide side) {
  side_ = side;
  configRepository_.saveSide(side);
}

Threshold PadService::getThreshold(uint8_t sensorIndex) const {
  if (sensorIndex >= EepromLayout::THRESHOLD_COUNT) {
    return Threshold(sensorIndex, EepromLayout::DEFAULT_THRESHOLD);
  }

  return Threshold(sensorIndex, thresholds_[sensorIndex]);
}

void PadService::setThreshold(const Threshold& threshold) {
  uint8_t index = threshold.getSensorIndex();
  int16_t value = threshold.getValue();

  if (index >= EepromLayout::THRESHOLD_COUNT) {
    return;
  }

  if (value < 0) {
    value = 0;
  }

  if (value > 1023) {
    value = 1023;
  }

  thresholds_[index] = value;
}

void PadService::saveThresholds() {
  for (uint8_t i = 0; i < EepromLayout::THRESHOLD_COUNT; ++i) {
    thresholdRepository_.save(Threshold(i, thresholds_[i]));
  }
}

SensorValue PadService::getCurrentValue(uint8_t sensorIndex) const {
  if (sensorIndex >= EepromLayout::THRESHOLD_COUNT) {
    return SensorValue(sensorIndex, 0);
  }

  return SensorValue(sensorIndex, currentValues_[sensorIndex]);
}

void PadService::updateRawValue(uint8_t sensorIndex, int16_t rawValue) {
  if (sensorIndex >= EepromLayout::THRESHOLD_COUNT) {
    return;
  }

  int16_t adjusted = rawValue - offsets_[sensorIndex];
  if (adjusted < 0) {
    adjusted = 0;
  }
  if (adjusted > 1023) {
    adjusted = 1023;
  }

  currentValues_[sensorIndex] = adjusted;
}

void PadService::calibrateOffset(uint8_t sensorIndex) {
  if (sensorIndex >= EepromLayout::THRESHOLD_COUNT) {
    return;
  }

  offsets_[sensorIndex] = currentValues_[sensorIndex];
}
