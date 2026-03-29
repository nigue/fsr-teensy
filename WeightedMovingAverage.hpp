#pragma once

#include "FsrConstants.hpp"  // para kWindowSize

class WeightedMovingAverage {
 public:
  // Constructor explícito con tamaño
  WeightedMovingAverage(size_t size)
      : size_(min(size, FsrConstants::kWindowSize)),
        cur_sum_(0),
        cur_weighted_sum_(0),
        values_{},
        cur_count_(0) {}

  // Método principal
  int16_t GetAverage(int16_t value) {
    // Add current value and remove oldest value
    int32_t next_sum = cur_sum_ + value - values_[cur_count_];

    // Update weighted sum
    int32_t next_weighted_sum =
        cur_weighted_sum_ + size_ * value - cur_sum_;

    cur_sum_ = next_sum;
    cur_weighted_sum_ = next_weighted_sum;

    values_[cur_count_] = value;
    cur_count_ = (cur_count_ + 1) % size_;

    // Sum of weights = 1 + 2 + ... + size_
    int16_t sum_weights = ((size_ * (size_ + 1)) / 2);

    return next_weighted_sum / sum_weights;
  }

  // Sin constructor por defecto
  WeightedMovingAverage() = delete;

 private:
  size_t size_;
  int32_t cur_sum_;
  int32_t cur_weighted_sum_;
  int16_t values_[FsrConstants::kWindowSize];
  size_t cur_count_;
};