#pragma once

#include <stdint.h>

#include "../eeprom/EepromLayout.h"
#include "../model/PadSide.h"
#include "../model/SensorValue.h"
#include "../model/Threshold.h"
#include "../repository/PadConfigRepository.h"
#include "../repository/ThresholdRepository.h"

class PadService {
 private:
  ThresholdRepository& thresholdRepository_;
  PadConfigRepository& configRepository_;

  int16_t thresholds_[EepromLayout::THRESHOLD_COUNT];
  int16_t currentValues_[EepromLayout::THRESHOLD_COUNT];
  int16_t offsets_[EepromLayout::THRESHOLD_COUNT];
  PadSide side_;

 public:
  PadService(ThresholdRepository& thresholdRepository,
             PadConfigRepository& configRepository);

  void initialize();

  PadSide getPadSide() const;
  void setPadSide(PadSide side);

  Threshold getThreshold(uint8_t sensorIndex) const;
  void setThreshold(const Threshold& threshold);
  void saveThresholds();

  SensorValue getCurrentValue(uint8_t sensorIndex) const;
  void updateRawValue(uint8_t sensorIndex, int16_t rawValue);
  void calibrateOffset(uint8_t sensorIndex);
};
