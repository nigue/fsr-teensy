#pragma once

#include "SensorObj.hpp"
#include "DDR.hpp"

class PanelObj {
private:
  SensorObj sensorA;
  SensorObj sensorB;
  const DDR::DDRButton buttonNumber;

  bool pressed;

public:
  PanelObj(SensorObj a, SensorObj b, DDR::DDRButton btn)
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

  DDR::DDRButton getButtonNumber() const {
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
      DDR::press(buttonNumber);
    } else {
      DDR::release(buttonNumber);
    }

    //Buttons::send();
  }
};