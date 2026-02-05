#pragma once

#include <Arduino.h>

#include "../service/PadService.h"

class SerialControl {
 private:
  PadService& service_;

  static const size_t BUFFER_SIZE = 64;
  char buffer_[BUFFER_SIZE];

  void printThresholds();
  void printValues();
  void calibrateOffsets();
  void updateThresholdFromBuffer();

 public:
  explicit SerialControl(PadService& service);

  void begin(unsigned long baudRate);
  void processIncoming();
};
