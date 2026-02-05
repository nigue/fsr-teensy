#pragma once

#include "../model/PadSide.h"
#include "../eeprom/EepromLayout.h"
#include "EepromStorage.h"

class PadConfigRepository {
 private:
  EepromStorage& storage_;

 public:
  explicit PadConfigRepository(EepromStorage& storage);

  PadSide loadSide() const;
  void saveSide(PadSide side);
  void initializeMagic();
};
