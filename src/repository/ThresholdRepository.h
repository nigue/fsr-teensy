#pragma once

#include <stdint.h>

#include "../model/Threshold.h"
#include "../eeprom/EepromLayout.h"
#include "EepromStorage.h"

class ThresholdRepository {
 private:
  EepromStorage& storage_;

 public:
  explicit ThresholdRepository(EepromStorage& storage);

  Threshold load(uint8_t sensorIndex) const;
  void save(const Threshold& threshold);
};
