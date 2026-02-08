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
