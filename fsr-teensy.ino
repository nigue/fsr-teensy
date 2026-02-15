#include "src/model/Threshold.h"

#include "src/plataform/ArduinoEepromStorage.h"
#include "src/repository/EepromHeaderRepository.h"
#include "src/repository/PadConfigRepository.h"
#include "src/repository/EepromHeaderRepository.h"
#include "src/service/SensorsService.h"
#include "src/service/CommandService.h"

ArduinoEepromStorage storage;
ThresholdRepository thresholdRepo(storage);
PadConfigRepository padRepo(storage);
EepromHeaderRepository headerRepo(storage);

SensorsService sensorsService(thresholdRepo);
CommandService commandService(sensorsService, padRepo, headerRepo);

void setup() {
  if (!headerRepo.isInitialized()) headerRepo.initialize();
}

void loop() {
  if (Serial.available()) commandService.execute(Serial.read());
}
