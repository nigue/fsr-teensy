# fsr-teensy

Proyecto para control de pad DDR con 8 sensores FSR en placas Teensy/Arduino.

## Arquitectura (3 capas)

- **Control**: procesa comandos seriales (`v`, `t`, `o`, `s`, `index valor`).
- **Servicio**: mantiene estado en RAM (thresholds, offsets y valores actuales).
- **Repository**: persiste configuración en EEPROM.

## Estructura

- `src/control`: comunicación externa.
- `src/service`: lógica de negocio y memoria RAM.
- `src/repository`: persistencia.
- `src/platform`: adaptadores concretos (EEPROM de Arduino).
- `src/model`: objetos de dominio inmutables (solo constructor + getters).
- `docs`: diagramas PlantUML.
- `test`: pruebas unitarias en C++.

## Compilar firmware

```bash
arduino-cli compile --fqbn teensy:avr:teensy41 .
```

## Ejecutar tests unitarios

```bash
g++ -std=c++17 -Wall -Wextra -Isrc \
  test/test_main.cpp \
  src/model/Threshold.cpp src/model/SensorValue.cpp \
  src/repository/ThresholdRepository.cpp src/repository/PadConfigRepository.cpp \
  src/service/PadService.cpp \
  -o test_runner && ./test_runner
```