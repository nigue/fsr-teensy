#include "SerialControl.h"

#include <stdlib.h>

SerialControl::SerialControl(PadService& service) : service_(service), buffer_{} {}

void SerialControl::begin(unsigned long baudRate) {
  Serial.begin(baudRate);
}

void SerialControl::processIncoming() {
  while (Serial.available() > 0) {
    size_t bytesRead = Serial.readBytesUntil('\n', buffer_, BUFFER_SIZE - 1);
    buffer_[bytesRead] = '\0';

    if (bytesRead == 0) {
      return;
    }

    char command = buffer_[0];

    if (command == 'v' || command == 'V') {
      printValues();
    } else if (command == 't' || command == 'T') {
      printThresholds();
    } else if (command == 'o' || command == 'O') {
      calibrateOffsets();
    } else if (command == 's' || command == 'S') {
      service_.saveThresholds();
      printThresholds();
    } else if (command >= '0' && command <= '9') {
      updateThresholdFromBuffer();
      printThresholds();
    }
  }
}

void SerialControl::printThresholds() {
  Serial.print("t");
  for (uint8_t i = 0; i < EepromLayout::THRESHOLD_COUNT; ++i) {
    Serial.print(" ");
    Serial.print(service_.getThreshold(i).getValue());
  }
  Serial.print("\n");
}

void SerialControl::printValues() {
  Serial.print("v");
  for (uint8_t i = 0; i < EepromLayout::THRESHOLD_COUNT; ++i) {
    Serial.print(" ");
    Serial.print(service_.getCurrentValue(i).getValue());
  }
  Serial.print("\n");
}

void SerialControl::calibrateOffsets() {
  for (uint8_t i = 0; i < EepromLayout::THRESHOLD_COUNT; ++i) {
    service_.calibrateOffset(i);
  }
}

void SerialControl::updateThresholdFromBuffer() {
  char* next = nullptr;
  unsigned long sensorIndex = strtoul(buffer_, &next, 10);

  if (sensorIndex >= EepromLayout::THRESHOLD_COUNT) {
    return;
  }

  long threshold = strtol(next, nullptr, 10);
  if (threshold < 0 || threshold > 1023) {
    return;
  }

  service_.setThreshold(Threshold(static_cast<uint8_t>(sensorIndex),
                                  static_cast<int16_t>(threshold)));
}
