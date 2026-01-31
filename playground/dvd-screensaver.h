#pragma once

#include "config.h"
#include "raylib.h"
#include <cstdio>

class DvdScreensaver {
  Color _color;

  Texture _texture;

  Rectangle _srcRec;
  Rectangle _destRec;

  Rectangle _collisionRec;

  Vector2 _origin;

  int _speedX = 2;
  int _speedY = 2;

  int _acceleration = 1;

  Config &_config;

public:
  DvdScreensaver() : _config(Config::instance()) {
    printf("DvdScreensaver started!\n");
    _texture = LoadTexture("./dvd.png");

    _srcRec.x = 0;
    _srcRec.y = 0;
    _srcRec.width = (float)_texture.width;
    _srcRec.height = (float)_texture.height;

    _destRec.width = 50.;
    _destRec.height = (50.f * _texture.height) / _texture.width;

    _collisionRec.width = 43;
    _collisionRec.height = 22;
    _collisionRec.x = 0;
    _collisionRec.y = 0;

    _origin.x = 0;
    _origin.y = 0;
  }

  ~DvdScreensaver() { UnloadTexture(_texture); }

  void update();

  void render();
};
