// Buttons.hpp
#pragma once

namespace Buttons {

  inline void start() {
    Joystick.begin();
    Joystick.useManualSend(true);
  }

  inline void press(uint8_t button_num) {
    Joystick.button(button_num, 1);
  }

  inline void release(uint8_t button_num) {
    Joystick.button(button_num, 0);
  }

  inline void send() {
    Joystick.send_now();
  }

}