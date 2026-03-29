#include "CommandService.h"

CommandService::CommandService(
  SensorsService& sensorsService,
  PadConfigRepository& padConfigRepository,
  EepromHeaderRepository& headerRepository
)
  : sensorsService_(sensorsService),
    padConfigRepository_(padConfigRepository),
    headerRepository_(headerRepository) {
}

void CommandService::execute(char command) {

  switch (static_cast<CommandEntry>(command)) {

    case CommandEntry::INFO:
      // Aquí podrías imprimir estado por Serial
      // Ejemplo: mostrar lado actual
      {
        PadSide side = padConfigRepository_.load();
        (void)side; // evitar warning si aún no usas Serial
      }
      break;

    case CommandEntry::SAVE_ALL_THRESHOLD:
      sensorsService_.persist();
      break;

    case CommandEntry::GET_ALL_THRESHOLD:
      {
        const int16_t* values = sensorsService_.getAll();
        (void)values; // aquí podrías enviarlos por Serial
      }
      break;

    case CommandEntry::SET_THRESHOLD_1:
      {
        sensorsService_.set(1, 50);
        const int16_t* values = sensorsService_.getAll();
        (void)values; // aquí podrías enviarlos por Serial
      }
      break;

    default:
      // comando desconocido
      break;
  }
}
