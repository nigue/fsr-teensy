#pragma once

#include "EepromStorage.h"
#include "../eeprom/EepromLayout.h"
#include "../model/Threshold.h"

class ThresholdRepository {
 public:
  static void save(const Threshold& threshold);
  static Threshold load(uint8_t index);
};
