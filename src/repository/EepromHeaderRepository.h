#pragma once

#include "EepromStorage.h"

class EepromHeaderRepository {

  private:
    EepromStorage& repository_;

  public:
    explicit EepromHeaderRepository(EepromStorage& repository);

    bool isInitialized() const;
    void initialize();
};
