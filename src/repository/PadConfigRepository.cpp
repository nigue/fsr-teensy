#include "PadConfigRepository.h"
#include "../eeprom/EepromLayout.h"

PadConfigRepository::PadConfigRepository(EepromStorage& repository)
    : repository_(repository) {}

PadSide PadConfigRepository::load() const {
  uint8_t raw = repository_.readByte(EepromLayout::PAD_SIDE_ADDR);

  if (raw == static_cast<uint8_t>(PadSide::RIGHT)) {
    return PadSide::RIGHT;
  }

  return PadSide::LEFT;
}

void PadConfigRepository::save(PadSide side) {
  repository_.writeByte(EepromLayout::PAD_SIDE_ADDR, static_cast<uint8_t>(side));
}

void PadConfigRepository::init() {
  uint8_t current = repository_.readByte(EepromLayout::MAGIC_ADDR);
  if (current != EepromLayout::MAGIC_VALUE) {
    save(PadSide::LEFT);
  }
}