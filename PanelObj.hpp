#pragma once

#include "SensorObj.hpp"
#include "LightObj.hpp"
#include "DDR.hpp"

class PanelObj {
private:
  SensorObj sensorA;
  SensorObj sensorB;
  const DDR::DDRButton buttonNumber;

  bool pressed;
  LightObj light;

public:
  PanelObj(SensorObj a, SensorObj b, DDR::DDRButton btn, LightObj light)
      : sensorA(a), sensorB(b), buttonNumber(btn), pressed(false), light(light) {}

  bool isPressed() const {
    return pressed;
  }

  void setPressed(bool state) {
    pressed = state;
  }

  void beginLight() {
    light.begin();
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
    light.set(pressed);
  }
};