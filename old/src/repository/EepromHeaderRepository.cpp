#include "EepromHeaderRepository.h"
#include "../eeprom/EepromLayout.h"

EepromHeaderRepository::EepromHeaderRepository(EepromStorage& repository)
  : repository_(repository) {
}

bool EepromHeaderRepository::isInitialized() const {
  return repository_.readByte(EepromLayout::MAGIC_ADDR) == EepromLayout::MAGIC_VALUE;
}

void EepromHeaderRepository::initialize() {
  if (!isInitialized()) {
    repository_.writeByte(EepromLayout::MAGIC_ADDR, EepromLayout::MAGIC_VALUE);
  }
}
