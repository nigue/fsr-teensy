#pragma once

namespace Pins {

  enum class Analog : uint8_t {
    A2 = ::A2,
    A3 = ::A3,
    A4 = ::A4,
    A5 = ::A5,
    A6 = ::A6,
    A7 = ::A7,
    A8 = ::A8,
    A9 = ::A9
  };

  inline uint8_t toInt(Analog pin) {
    return static_cast<uint8_t>(pin);
  }

  inline int16_t analogRead(Pins::Analog pin) {
    return ::analogRead(static_cast<uint8_t>(pin));
  }

}