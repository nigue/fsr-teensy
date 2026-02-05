#include "Threshold.h"

Threshold::Threshold(uint8_t sensorIndex, int16_t value)
    : sensorIndex_(sensorIndex), value_(value) {}

uint8_t Threshold::getSensorIndex() const {
  return sensorIndex_;
}

int16_t Threshold::getValue() const {
  return value_;
}
