#include "PadObj.hpp"
#include "SensorObj.hpp"
#include "Pins.hpp"
#include "Buttons.hpp"

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
PanelObj leftPanel(sL1, sL2, 5);
PanelObj downPanel(sD1, sD2, 8);
PanelObj upPanel(sU1, sU2, 6);
PanelObj rightPanel(sR1, sR2, 7);

// --- Pad completo ---
PadObj pad(leftPanel, downPanel, upPanel, rightPanel);

void setup() {
  Buttons::start();

}

unsigned long lastSend = 0;
long loopTime = -1;
void loop() {
  unsigned long startMicros = micros();
  static bool willSend;
  willSend = (loopTime == -1 || startMicros - lastSend + loopTime >= 1000);

  pad.update();

  if (willSend) {
    lastSend = startMicros;
    Buttons::send();
  }

  if (loopTime == -1) {
    loopTime = micros() - startMicros;
  }
}