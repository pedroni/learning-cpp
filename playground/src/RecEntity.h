#pragma once

#include "config.h"
#include "entity.h"
#include "helpers.h"
#include "raylib.h"

class RecEntity : public Entity {
public:
  float x;
  float y;
  float width;
  float height;
  Color color = BLACK;

  RecEntity() {}
  RecEntity(float x, float y, float width, float height, Color color)
      : x(x), y(y), width(width), height(height), color(color) {}

  // probably a killer for performance but it's a small struct?
  Rectangle getRec() { return Rectangle{x, y, width, height}; }

  void update() override {};
  void render() override {
    DrawRectangle(x, y, width, height, color);

    if (GetConfig().isDebugging()) {
      DrawRectangleLines(x, y, width, height, PURPLE);
    }
  }
};
