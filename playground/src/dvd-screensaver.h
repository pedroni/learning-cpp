#pragma once

#include "config.h"
#include "raylib.h"
#include <cstdio>

class DvdScreensaver {
  Color color_;

  Texture texture_;

  Rectangle srcRec_;
  Rectangle destRec_;

  Rectangle collisionRec_;

  Vector2 origin_;

  int speedX_ = 2;
  int speedY_ = 2;

  int acceleration_ = 1;

  Config &config_;

public:
  DvdScreensaver() : config_(Config::instance()) {
    printf("DvdScreensaver started!\n");
    texture_ = LoadTexture("./assets/dvd.png");

    srcRec_.x = 0;
    srcRec_.y = 0;
    srcRec_.width = (float)texture_.width;
    srcRec_.height = (float)texture_.height;

    destRec_.width = 50.;
    destRec_.height = (50.f * texture_.height) / texture_.width;

    collisionRec_.width = 43;
    collisionRec_.height = 22;
    collisionRec_.x = 0;
    collisionRec_.y = 0;

    origin_.x = 0;
    origin_.y = 0;
  }

  ~DvdScreensaver() { UnloadTexture(texture_); }

  void update();

  void render();
};
