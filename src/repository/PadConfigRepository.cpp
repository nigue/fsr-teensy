#include "PadConfigRepository.h"

PadConfigRepository::PadConfigRepository(EepromStorage& storage)
    : storage_(storage) {}

PadSide PadConfigRepository::loadSide() const {
  uint8_t raw = storage_.readByte(EepromLayout::PAD_SIDE_ADDR);

  if (raw == static_cast<uint8_t>(PadSide::RIGHT)) {
    return PadSide::RIGHT;
  }

  return PadSide::LEFT;
}

void PadConfigRepository::saveSide(PadSide side) {
  storage_.writeByte(EepromLayout::PAD_SIDE_ADDR, static_cast<uint8_t>(side));
}

void PadConfigRepository::initializeMagic() {
  uint8_t current = storage_.readByte(EepromLayout::MAGIC_ADDR);
  if (current != EepromLayout::MAGIC_VALUE) {
    storage_.writeByte(EepromLayout::MAGIC_ADDR, EepromLayout::MAGIC_VALUE);
    saveSide(PadSide::LEFT);
  }
}
