#pragma once

#include <EEPROM.h>
#include "../model/PadSide.h"
#include "../eeprom/EepromLayout.h"

class PadConfigRepository {
public:
  static void saveSide(PadSide side) {
    EEPROM.put(
      EepromLayout::PAD_SIDE_ADDR, 
      static_cast<uint8_t>(side)
    );
  }

  static PadSide loadSide() {
    uint8_t raw;
    EEPROM.get(EepromLayout::PAD_SIDE_ADDR, raw);
    return static_cast<PadSide>(raw);
  }

  static bool existsSide() {
    uint8_t raw;
    EEPROM.get(EepromLayout::PAD_SIDE_ADDR, raw);
    return raw != 0xFF;
  }
};