#pragma once

#include "PanelObj.hpp"

class PadObj {
private:
  PanelObj left;
  PanelObj down;
  PanelObj up;
  PanelObj right;

public:
  // Constructor
  PadObj(const PanelObj& l,
         const PanelObj& d,
         const PanelObj& u,
         const PanelObj& r)
      : left(l), down(d), up(u), right(r) {}

  // Getters
  PanelObj& getLeft() {
    return left;
  }

  PanelObj& getDown() {
    return down;
  }

  PanelObj& getUp() {
    return up;
  }

  PanelObj& getRight() {
    return right;
  }

  void update() {
    left.update();
    down.update();
    up.update();
    right.update();
  }

  void beginLights() {
    left.beginLight();
    down.beginLight();
    up.beginLight();
    right.beginLight();
  }
};