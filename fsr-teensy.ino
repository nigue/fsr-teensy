#include "src/model/Threshold.h"

#include "src/plataform/ArduinoEepromStorage.h"
#include "src/repository/EepromHeaderRepository.h"

ArduinoEepromStorage storage;
EepromHeaderRepository headerRepo(storage);

void setup() {
    
  if (!headerRepo.isInitialized()) {
    headerRepo.initialize();
  }
}

void loop() {}
