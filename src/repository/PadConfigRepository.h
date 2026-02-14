#pragma once

#include "../model/PadSide.h"
#include "EepromStorage.h"

class PadConfigRepository {

  private:
    EepromStorage& repository_;
    PadSide currentSide_;
    void init();
  public:
    explicit PadConfigRepository(EepromStorage& repository);
    PadSide load() const;
    void save(PadSide side);
    
};