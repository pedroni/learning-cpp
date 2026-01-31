#include "dvd-screensaver.h"
#include "config.h"
#include "helpers.h"
#include "raylib.h"
#include <cstdio>

void DvdScreensaver::update() {
  if (_config.isDebugging()) {
    printf("x(%f) y(%f)\n", _collisionRec.x, _collisionRec.y);
  }
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    _acceleration += 1;
  } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    _acceleration -= 1;
  }

  // Update
  _collisionRec.x += _speedX * _acceleration;
  _collisionRec.y += _speedY * _acceleration;

  _destRec.x = _collisionRec.x - 5;
  _destRec.y = _collisionRec.y - 15;

  if (_collisionRec.x >= _config.SCREN_WIDTH - _collisionRec.width ||
      _collisionRec.x <= 0) {
    _speedX = -1 * _speedX;
    _color = GetRandomColor();
  }

  if (_collisionRec.y >= _config.SCREEN_HEIGHT - _collisionRec.height ||
      _collisionRec.y <= 0) {
    _speedY = -1 * _speedY;
    _color = GetRandomColor();
  }
}

void DvdScreensaver::render() {
  DrawTexturePro(_texture, _srcRec, _destRec, _origin, 0, _color);

  if (_config.isDebugging()) {
    DrawRectangleLinesEx(_collisionRec, 1.f, YELLOW);
  }
}
