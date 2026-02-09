#define CATCH_CONFIG_MAIN
#include "third_party/catch2/catch.hpp"

#include "../src/repository/PadConfigRepository.h"
#include "../src/eeprom/EepromLayout.h"
#include "mocks/MockEepromStorage.h"

TEST_CASE("PadConfigRepository guarda y carga PadSide") {

  MockEepromStorage mock;
  PadConfigRepository repo(mock);

  INFO("Guardando PadSide::RIGHT");
  repo.save(PadSide::RIGHT);

  INFO("Cargando PadSide desde EEPROM");
  PadSide loaded = repo.load();

  CAPTURE(static_cast<int>(loaded));
  REQUIRE(loaded == PadSide::RIGHT);
}

TEST_CASE("PadConfigRepository init setea LEFT si EEPROM no esta inicializada") {

  MockEepromStorage mock;
  PadConfigRepository repo(mock);

  INFO("EEPROM sin MAGIC_VALUE");
  REQUIRE(mock.memory.find(EepromLayout::MAGIC_ADDR) == mock.memory.end());

  repo.init();

  uint8_t raw = mock.memory[EepromLayout::PAD_SIDE_ADDR];
  CAPTURE(raw);

  REQUIRE(raw == static_cast<uint8_t>(PadSide::LEFT));
}

TEST_CASE("PadConfigRepository init no sobreescribe si EEPROM ya esta inicializada") {

  MockEepromStorage mock;
  PadConfigRepository repo(mock);

  INFO("Simulando EEPROM inicializada");
  mock.memory[EepromLayout::MAGIC_ADDR] = EepromLayout::MAGIC_VALUE;
  mock.memory[EepromLayout::PAD_SIDE_ADDR] = static_cast<uint8_t>(PadSide::RIGHT);

  repo.init();

  uint8_t raw = mock.memory[EepromLayout::PAD_SIDE_ADDR];
  CAPTURE(raw);

  REQUIRE(raw == static_cast<uint8_t>(PadSide::RIGHT));
}

TEST_CASE("PadConfigRepository load retorna LEFT ante valor inesperado") {

  MockEepromStorage mock;
  PadConfigRepository repo(mock);

  INFO("Escribiendo valor invalido en EEPROM");
  mock.memory[EepromLayout::PAD_SIDE_ADDR] = 0xFF;

  PadSide loaded = repo.load();
  CAPTURE(static_cast<int>(loaded));

  REQUIRE(loaded == PadSide::LEFT);
}
