#pragma once

#include "../model/CommandEntry.h"
#include "../service/SensorsService.h"
#include "../repository/PadConfigRepository.h"
#include "../repository/EepromHeaderRepository.h"

class CommandService {

  private:
    SensorsService& sensorsService_;
    PadConfigRepository& padConfigRepository_;
    EepromHeaderRepository& headerRepository_;

  public:
    CommandService(
      SensorsService& sensorsService,
      PadConfigRepository& padConfigRepository,
      EepromHeaderRepository& headerRepository
    );

    // Ejecuta un comando recibido (por ejemplo desde Serial)
    void execute(char command);
};
