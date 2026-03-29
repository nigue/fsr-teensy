#pragma once

#include <stddef.h>
#include <stdint.h>

namespace EepromLayout {

  // ──────────────
  // Header global
  // ──────────────
  constexpr size_t MAGIC_ADDR = 0;   // 1 byte
  constexpr uint8_t MAGIC_VALUE = 0x42;

  // ──────────────
  // PadSide
  // ──────────────
  constexpr size_t PAD_SIDE_ADDR = 1; // 1 byte

  // ──────────────
  // Thresholds
  // ──────────────
  constexpr size_t THRESHOLD_BASE_ADDR = 2;

  constexpr size_t THRESHOLD_COUNT = 8;
  constexpr size_t THRESHOLD_SIZE  = sizeof(int16_t);

  constexpr size_t thresholdAddr(size_t index) {
    return THRESHOLD_BASE_ADDR + index * THRESHOLD_SIZE;
  }

}