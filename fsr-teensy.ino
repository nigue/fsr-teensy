#include "PadObj.hpp"
#include "SensorObj.hpp"
#include "Pins.hpp"
#include "DDR.hpp"
#include "SerialCommand.hpp"

// --- Sensores ---
SensorObj sL1(Pins::Analog::A2, 199);
SensorObj sL2(Pins::Analog::A3, 136);

SensorObj sU1(Pins::Analog::A4, 157);
SensorObj sU2(Pins::Analog::A5, 94);

SensorObj sR1(Pins::Analog::A6, 39);
SensorObj sR2(Pins::Analog::A7, 150);

SensorObj sD1(Pins::Analog::A8, 176);
SensorObj sD2(Pins::Analog::A9, 81);

// --- Panels ---
PanelObj leftPanel(sL1, sL2, DDR::DDRButton::LEFT);
PanelObj downPanel(sD1, sD2, DDR::DDRButton::DOWN);
PanelObj upPanel(sU1, sU2, DDR::DDRButton::UP);
PanelObj rightPanel(sR1, sR2, DDR::DDRButton::RIGHT);

// --- Pad completo ---
PadObj pad(leftPanel, downPanel, upPanel, rightPanel);

SerialCommand* serialCmd;
void setup() {
  DDR::start();
  serialCmd = new SerialCommand(9600);
}

unsigned long lastSend = 0;
long loopTime = -1;
void loop() {
  unsigned long startMicros = micros();
  static bool willSend;
  willSend = (loopTime == -1 || startMicros - lastSend + loopTime >= 1000);

  pad.update();
  serialCmd->handle();
  if (willSend) {
    lastSend = startMicros;
    DDR::send();
  }

  if (loopTime == -1) {
    loopTime = micros() - startMicros;
  }
}