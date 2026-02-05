#pragma once

#include <stdint.h>

class SensorValue {
 private:
  uint8_t sensorIndex_;
  int16_t value_;

 public:
  SensorValue(uint8_t sensorIndex, int16_t value);

  uint8_t getSensorIndex() const;
  int16_t getValue() const;
};
