#include "PadConfigRepository.h"
#include "../eeprom/EepromLayout.h"

PadConfigRepository::PadConfigRepository(EepromStorage& storage)
    : storage_(storage) {}

PadSide PadConfigRepository::load() const {
  uint8_t raw = storage_.readByte(EepromLayout::PAD_SIDE_ADDR);

  if (raw == static_cast<uint8_t>(PadSide::RIGHT)) {
    return PadSide::RIGHT;
  }

  return PadSide::LEFT;
}

void PadConfigRepository::save(PadSide side) {
  storage_.writeByte(EepromLayout::PAD_SIDE_ADDR, static_cast<uint8_t>(side));
}

void PadConfigRepository::init() {
  uint8_t current = storage_.readByte(EepromLayout::MAGIC_ADDR);
  if (current != EepromLayout::MAGIC_VALUE) {
    save(PadSide::LEFT);
  }
}