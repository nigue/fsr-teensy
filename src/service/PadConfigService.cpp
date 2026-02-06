#include "PadConfigService.h"
#include "../repository/PadConfigRepository.h"

PadConfigService::PadConfigService(PadConfigRepository& repo)
  : repository_(repo),
    currentSide_(PAD_LEFT),
    hasValue_(false),
    dirty_(false) {}

void PadConfigService::init() {
  PadSide side;
  if (repository_.existsSide()) {
    currentSide_ = side;
    hasValue_ = true;
    dirty_ = false;
  } else {
    currentSide_ = PAD_LEFT; // valor por defecto
    hasValue_ = false;
    dirty_ = false;
  }
}

PadSide PadConfigService::getPadSide() const {
  return currentSide_;
}

void PadConfigService::setPadSide(PadSide side) {
  if (currentSide_ == side) {
    return;
  }
  currentSide_ = side;
  dirty_ = true;
}

void PadConfigService::saveIfNeeded() {
  if (!dirty_) {
    return;
  }

  repository_.saveSide(currentSide_);
  dirty_ = false;
  hasValue_ = true;
}
