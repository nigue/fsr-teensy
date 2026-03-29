#pragma once

#include <stdint.h>
#include "../model/Threshold.h"
#include "../repository/ThresholdRepository.h"
#include "../eeprom/EepromLayout.h"

class SensorsService {

  private:
    static constexpr uint8_t SENSOR_COUNT = EepromLayout::THRESHOLD_COUNT;

    ThresholdRepository& repository_;
    int16_t sensors_[SENSOR_COUNT];

  public:
    explicit SensorsService(ThresholdRepository& repository);

    // Setea el valor en RAM (no persiste)
    void set(uint8_t index, int16_t value);

    // Devuelve puntero al array completo
    const int16_t* getAll() const;

    // Guarda todos los sensores en EEPROM
    void persist();
};
