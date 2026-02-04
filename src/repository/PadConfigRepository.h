#pragma once

#include <EEPROM.h>
#include "../model/PadSide.h"
#include "../eeprom/EepromLayout.h"

//todo aplicar una lectura antes de guardar, si hay algo no guardar
// tal vez aplicar un valor booleano que indique guardado forsoso
class PadConfigRepository {
public:
  static void saveSide(PadSide side) {
    EEPROM.put(EepromLayout::PAD_SIDE_ADDR, side);
  }

  static PadSide loadSide() {
    uint8_t raw;
    EEPROM.get(EepromLayout::PAD_SIDE_ADDR, raw);
    return static_cast<PadSide>(raw);
  }
};