#pragma once

#include <EEPROM.h>
#include "../model/Threshold.h"
#include "../eeprom/EepromLayout.h"

class ThresholdRepository {
public:
  static void save(const Threshold& threshold) {
    uint8_t index = threshold.getSensorIndex();
    if (index >= EepromLayout::THRESHOLD_COUNT) return;

    EEPROM.put(
      EepromLayout::thresholdAddr(index),
      threshold.getValue()
    );
  }

  static Threshold load(uint8_t index) {
    if (index >= EepromLayout::THRESHOLD_COUNT) {
      return Threshold(index, 0);
    }

    int16_t value;
    EEPROM.get(
      EepromLayout::thresholdAddr(index),
      value
    );

    return Threshold(index, value);
  }
};
