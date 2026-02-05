#include "SensorValue.h"

SensorValue::SensorValue(uint8_t sensorIndex, int16_t value)
    : sensorIndex_(sensorIndex), value_(value) {}

uint8_t SensorValue::getSensorIndex() const {
  return sensorIndex_;
}

int16_t SensorValue::getValue() const {
  return value_;
}
