#include "PadConfigRepository.h"
#include "../eeprom/EepromLayout.h"

PadConfigRepository::PadConfigRepository(EepromStorage& repository)
    : repository_(repository),
      currentSide_(PadSide::LEFT) {

  uint8_t raw = repository_.readByte(EepromLayout::PAD_SIDE_ADDR);

  if (raw == static_cast<uint8_t>(PadSide::RIGHT)) {
    currentSide_ = PadSide::RIGHT;
  }
}

PadSide PadConfigRepository::load() const {
  return currentSide_;
}

void PadConfigRepository::save(PadSide side) {
  currentSide_ = side;
  repository_.writeByte(EepromLayout::PAD_SIDE_ADDR, static_cast<uint8_t>(side));
}
