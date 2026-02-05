#pragma once

#include <stddef.h>
#include <stdint.h>

namespace EepromLayout {

constexpr uint8_t MAGIC_VALUE = 0x42;
constexpr size_t MAGIC_ADDR = 0;
constexpr size_t PAD_SIDE_ADDR = 1;

constexpr size_t THRESHOLD_COUNT = 8;
constexpr int16_t DEFAULT_THRESHOLD = 512;
constexpr size_t THRESHOLD_BASE_ADDR = 2;
constexpr size_t THRESHOLD_BYTES = sizeof(int16_t);

constexpr size_t thresholdLowAddr(uint8_t sensorIndex) {
  return THRESHOLD_BASE_ADDR + sensorIndex * THRESHOLD_BYTES;
}

constexpr size_t thresholdHighAddr(uint8_t sensorIndex) {
  return thresholdLowAddr(sensorIndex) + 1;
}

}  // namespace EepromLayout
