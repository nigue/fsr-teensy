#define CATCH_CONFIG_MAIN
#include "third_party/catch2/catch.hpp"

#include "../src/repository/PadConfigRepository.h"
#include "../src/eeprom/EepromLayout.h"
#include "mocks/MockEepromStorage.h"

TEST_CASE("PadConfigRepository guarda y carga PadSide") {

  MockEepromStorage mock;
  PadConfigRepository repo(mock);

  repo.save(PadSide::RIGHT);
  PadSide loaded = repo.load();

  REQUIRE(loaded == PadSide::RIGHT);
}
