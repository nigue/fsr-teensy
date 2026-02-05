#include "src/control/SerialControl.h"
#include "src/platform/ArduinoEepromStorage.h"
#include "src/repository/PadConfigRepository.h"
#include "src/repository/ThresholdRepository.h"
#include "src/service/PadService.h"

namespace {

constexpr unsigned long SERIAL_BAUD_RATE = 115200;
constexpr uint8_t SENSOR_COUNT = EepromLayout::THRESHOLD_COUNT;

const uint8_t SENSOR_PINS[SENSOR_COUNT] = {
    A0, A1, A2, A3, A4, A5, A6, A7,
};

ArduinoEepromStorage eepromStorage;
ThresholdRepository thresholdRepository(eepromStorage);
PadConfigRepository padConfigRepository(eepromStorage);
PadService padService(thresholdRepository, padConfigRepository);
SerialControl serialControl(padService);

}  // namespace

void setup() {
  serialControl.begin(SERIAL_BAUD_RATE);
  padService.initialize();
}

void loop() {
  for (uint8_t i = 0; i < SENSOR_COUNT; ++i) {
    int16_t rawValue = analogRead(SENSOR_PINS[i]);
    padService.updateRawValue(i, rawValue);
  }

  serialControl.processIncoming();
}
