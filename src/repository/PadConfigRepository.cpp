#include "PadConfigRepository.h"
#include "../eeprom/EepromLayout.h"

PadConfigRepository::PadConfigRepository(EepromStorage& repository)
    : repository_(repository),
      currentSide_(PadSide::LEFT) {
  init();
}

PadSide PadConfigRepository::load() const {
  return currentSide_;
}

void PadConfigRepository::save(PadSide side) {
  currentSide_ = side;
  repository_.writeByte(EepromLayout::PAD_SIDE_ADDR, static_cast<uint8_t>(side));
}

void PadConfigRepository::init() {
  //todo La inicializacion de la memoria puede ser otro repositorio
  uint8_t magic = repository_.readByte(EepromLayout::MAGIC_ADDR);

  if (magic != EepromLayout::MAGIC_VALUE) {
    // EEPROM no inicializada
    repository_.writeByte(EepromLayout::MAGIC_ADDR, EepromLayout::MAGIC_VALUE);
    save(PadSide::LEFT);
  } else {
    // EEPROM ya inicializada → cargar valor
    uint8_t raw = repository_.readByte(EepromLayout::PAD_SIDE_ADDR);

    if (raw == static_cast<uint8_t>(PadSide::RIGHT)) {
      currentSide_ = PadSide::RIGHT;
    } else {
      currentSide_ = PadSide::LEFT;
    }
  }
}