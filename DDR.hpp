#pragma once

#include <stdint.h>
#include "usb_joystick.h"

namespace DDR {

  enum DDRButton : uint8_t {
    LEFT  = 0, // HID Button 1
    DOWN  = 1, // HID Button 2
    UP    = 2, // HID Button 3
    RIGHT = 3  // HID Button 4
  };

  static uint8_t state = 0;

  inline void start() {
    state = 0;
  }

  inline void press(DDRButton button) {
    uint8_t b = static_cast<uint8_t>(button);
    if (b < 4) {
      state |= (1 << b);
    }
  }

  inline void release(DDRButton button) {
    uint8_t b = static_cast<uint8_t>(button);
    if (b < 4) {
      state &= ~(1 << b);
    }
  }

  inline void send() {
    usb_joystick_data[0] = state;
    usb_joystick_send();
  }

}