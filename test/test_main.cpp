#include <assert.h>
#include <stdint.h>

#include <array>
#include <iostream>

#include "../src/eeprom/EepromLayout.h"
#include "../src/model/PadSide.h"
#include "../src/model/Threshold.h"
#include "../src/repository/EepromStorage.h"
#include "../src/repository/PadConfigRepository.h"
#include "../src/repository/ThresholdRepository.h"
#include "../src/service/PadService.h"

class FakeEepromStorage : public EepromStorage {
 private:
  std::array<uint8_t, 128> memory_{};

 public:
  uint8_t readByte(size_t address) const override {
    return memory_[address];
  }

  void writeByte(size_t address, uint8_t value) override {
    memory_[address] = value;
  }
};

void testThresholdRepositoryRoundTrip() {
  FakeEepromStorage storage;
  ThresholdRepository repository(storage);

  repository.save(Threshold(2, 777));
  Threshold loaded = repository.load(2);

  assert(loaded.getSensorIndex() == 2);
  assert(loaded.getValue() == 777);
}

void testPadServiceLoadsDefaultsWhenInvalid() {
  FakeEepromStorage storage;
  ThresholdRepository thresholdRepository(storage);
  PadConfigRepository configRepository(storage);
  PadService service(thresholdRepository, configRepository);

  storage.writeByte(EepromLayout::thresholdLowAddr(1), 0xFF);
  storage.writeByte(EepromLayout::thresholdHighAddr(1), 0xFF);

  service.initialize();
  Threshold threshold = service.getThreshold(1);

  assert(threshold.getValue() == EepromLayout::DEFAULT_THRESHOLD);
}

void testPadServiceSetAndPersistThresholds() {
  FakeEepromStorage storage;
  ThresholdRepository thresholdRepository(storage);
  PadConfigRepository configRepository(storage);
  PadService service(thresholdRepository, configRepository);

  service.initialize();
  service.setThreshold(Threshold(0, 200));
  service.setThreshold(Threshold(7, 900));
  service.saveThresholds();

  Threshold loaded0 = thresholdRepository.load(0);
  Threshold loaded7 = thresholdRepository.load(7);

  assert(loaded0.getValue() == 200);
  assert(loaded7.getValue() == 900);
}

void testPadSidePersistence() {
  FakeEepromStorage storage;
  ThresholdRepository thresholdRepository(storage);
  PadConfigRepository configRepository(storage);
  PadService service(thresholdRepository, configRepository);

  service.initialize();
  service.setPadSide(PadSide::RIGHT);

  PadSide loaded = configRepository.loadSide();
  assert(loaded == PadSide::RIGHT);
}

int main() {
  testThresholdRepositoryRoundTrip();
  testPadServiceLoadsDefaultsWhenInvalid();
  testPadServiceSetAndPersistThresholds();
  testPadSidePersistence();

  std::cout << "All tests passed\n";
  return 0;
}
