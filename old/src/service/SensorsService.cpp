#include "SensorsService.h"

SensorsService::SensorsService(ThresholdRepository& repository)
  : repository_(repository) {

  // Inicializamos desde EEPROM al arrancar
  for (uint8_t i = 0; i < SENSOR_COUNT; ++i) {
    sensors_[i] = repository_.load(i).getValue();
  }
}

void SensorsService::set(uint8_t index, int16_t value) {
  if (index >= SENSOR_COUNT) return;

  sensors_[index] = value;
}

const int16_t* SensorsService::getAll() const {
  return sensors_;
}

void SensorsService::persist() {
  for (uint8_t i = 0; i < SENSOR_COUNT; ++i) {
    repository_.save(Threshold(i, sensors_[i]));
  }
}
