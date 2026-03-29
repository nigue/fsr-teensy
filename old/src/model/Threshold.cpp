#include "Threshold.h"

Threshold::Threshold(uint8_t sensorIndex, int16_t value)
  : sensorIndex(sensorIndex), value(value) {}

uint8_t Threshold::getSensorIndex() const {
  return sensorIndex;
}

int16_t Threshold::getValue() const {
  return value;
}
