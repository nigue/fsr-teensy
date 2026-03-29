#pragma once

#include <math.h>  // para sqrt
#include "WeightedMovingAverage.hpp"

class HullMovingAverage {
 public:
  // Constructor explícito
  HullMovingAverage(size_t size)
      : wma1_(size / 2),
        wma2_(size),
        hull_(static_cast<size_t>(sqrt(size))) {}

  // Método principal
  int16_t GetAverage(int16_t value) {
    int16_t wma1_value = wma1_.GetAverage(value);
    int16_t wma2_value = wma2_.GetAverage(value);
    int16_t hull_value = hull_.GetAverage(2 * wma1_value - wma2_value);

    return hull_value;
  }

  // Sin constructor por defecto
  HullMovingAverage() = delete;

 private:
  WeightedMovingAverage wma1_;
  WeightedMovingAverage wma2_;
  WeightedMovingAverage hull_;
};