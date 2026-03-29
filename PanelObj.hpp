#pragma once

#include "SensorObj.hpp"
#include "Buttons.hpp"

class PanelObj {
private:
  SensorObj sensorA;
  SensorObj sensorB;
  const uint8_t buttonNumber;

  bool pressed;

public:
  PanelObj(SensorObj a, SensorObj b, uint8_t btn)
      : sensorA(a), sensorB(b), buttonNumber(btn), pressed(false) {}

  bool isPressed() const {
    return pressed;
  }

  void setPressed(bool state) {
    pressed = state;
  }

  SensorObj& getSensorA() {
    return sensorA;
  }

  SensorObj& getSensorB() {
    return sensorB;
  }

  uint8_t getButtonNumber() const {
    return buttonNumber;
  }

  void update() {
    sensorA.update();
    sensorB.update();

    bool current = sensorA.isPressed() || sensorB.isPressed();
    handleStateChange(current);
  }

  void handleStateChange(bool current) {
    if (current == pressed) return;

    pressed = current;

    if (pressed) {
      Buttons::press(buttonNumber);
    } else {
      Buttons::release(buttonNumber);
    }

    //Buttons::send();
  }
};