#pragma once

#include "../model/PadSide.h"
#include "EepromStorage.h"

class PadConfigRepository {

  private:
    EepromStorage& storage_;
  public:
    explicit PadConfigRepository(EepromStorage& storage);
    PadSide load() const;
    void save(PadSide side);
    void init();

};