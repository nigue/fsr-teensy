#pragma once

#include "Pins.hpp"
#include "HullMovingAverage.hpp"
#include "FsrConstants.hpp"

class SensorObj {
private:
  Pins::Analog pin;
  int16_t threshold;
  int16_t sensorValue;
  HullMovingAverage hma;

public:
  // Constructor
  SensorObj(Pins::Analog p, int16_t t)
      : pin(p), threshold(t), sensorValue(0), hma(FsrConstants::kWindowSize) {}

  // 🔥 Lee el sensor y actualiza el valor filtrado
  void update() {
    int16_t offset = 0;
    int16_t raw = Pins::analogRead(pin);   // 👈 usamos tu namespace
    sensorValue = hma.GetAverage(raw) - offset;     // 👈 aplicamos filtro
    sensorValue = sensorValue < 5 ? 0 : constrain(sensorValue, 0, 1023);
  }

  // Opcional: acceso al valor crudo filtrado
  int16_t getValue() const {
    return sensorValue;
  }

  // Lógica de presión
  bool isPressed() const {
    int16_t delta = 1;
    return sensorValue > threshold + delta;
  }

  // Getters / setters básicos
  Pins::Analog getPin() const { return pin; }
  void setPin(Pins::Analog p) { pin = p; }

  int16_t getThreshold() const { return threshold; }
  void setThreshold(int16_t t) { threshold = t; }
};