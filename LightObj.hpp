#pragma once

class LightObj {
private:
  int pin;
public:
  LightObj(int pin = -1) : pin(pin) {}
  void begin() { if (pin >= 0) pinMode(pin, OUTPUT); }
  void set(bool on) {
    if (pin < 0) return;
    digitalWrite(pin, on ? HIGH : LOW);
  }
  bool exists() const { return pin >= 0; }
};