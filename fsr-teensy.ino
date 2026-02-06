#include "src/model/Threshold.h"
#include "src/model/PadSide.h"
#include "src/repository/PadConfigRepository.h"
#include "src/repository/ThresholdRepository.h"

//todo namespace
Threshold threshold(1, 512);

void setup() {
  PadSide side = PAD_LEFT;
  PadConfigRepository::saveSide(side);

  Threshold t0(0, 512);
  Threshold t1(1, 700);

  ThresholdRepository::save(t0);
  ThresholdRepository::save(t1);

  //Threshold loaded = ThresholdRepository::load(0);
}

void loop() {}
