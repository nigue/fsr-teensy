#define CATCH_CONFIG_MAIN
#include "third_party/catch2/catch.hpp"

#include "../src/repository/PadConfigRepository.h"
#include "../src/eeprom/EepromLayout.h"
#include "mocks/MockEepromStorage.h"

TEST_CASE("save actualiza RAM y EEPROM") {

  MockEepromStorage mock;
  PadConfigRepository repo(mock);

  repo.save(PadSide::RIGHT);

  SECTION("load devuelve el valor en RAM") {
    REQUIRE(repo.load() == PadSide::RIGHT);
  }

  SECTION("EEPROM contiene el valor guardado") {
    REQUIRE(mock.memory[EepromLayout::PAD_SIDE_ADDR] == static_cast<uint8_t>(PadSide::RIGHT));
  }
}
