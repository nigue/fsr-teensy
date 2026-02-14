#pragma once

#include "../model/PadSide.h"
#include "../plataform/ArduinoEepromStorage.h"

class PadConfigRepository {

  private:
    EepromStorage& repository_;
    PadSide currentSide_;
  public:
    explicit PadConfigRepository(EepromStorage& repository);

    PadSide load() const;
    void save(PadSide side);
    
};