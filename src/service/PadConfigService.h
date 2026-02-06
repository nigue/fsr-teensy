#pragma once

#include "../model/PadSide.h"
#include "../repository/PadConfigRepository.h"

class PadConfigRepository;

class PadConfigService {
public:
  explicit PadConfigService(PadConfigRepository& repo);

  void init();

  PadSide getPadSide() const;
  void setPadSide(PadSide side);

  void saveIfNeeded();

private:
  PadConfigRepository& repository_;

  PadSide currentSide_;
  bool hasValue_;
  bool dirty_;
};
