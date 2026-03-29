#pragma once

#include <stdint.h>

class Threshold {
  private:
    uint8_t sensorIndex;
    int16_t value;

  public:
    Threshold(uint8_t sensorIndex, int16_t value);

    uint8_t getSensorIndex() const;
    int16_t getValue() const;
};
