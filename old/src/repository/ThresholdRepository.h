#pragma once

#include <stdint.h>
#include "../model/Threshold.h"
#include "../plataform/ArduinoEepromStorage.h"

class ThresholdRepository {

  private:
    EepromStorage& repository_;

  public:
    explicit ThresholdRepository(EepromStorage& repository);

    void save(const Threshold& threshold);
    Threshold load(uint8_t index) const;
};