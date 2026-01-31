#include "dvd-screensaver.h"
#include "config.h"
#include "helpers.h"
#include "raylib.h"
#include <cstdio>

void DvdScreensaver::update() {
  if (config_.isDebugging()) {
    printf("x(%f) y(%f)\n", collisionRec_.x, collisionRec_.y);
  }

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    acceleration_ += 1;
  } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    acceleration_ -= 1;
  }

  // Update
  collisionRec_.x += speedX_ * acceleration_;
  collisionRec_.y += speedY_ * acceleration_;

  destRec_.x = collisionRec_.x - 5;
  destRec_.y = collisionRec_.y - 15;

  if (collisionRec_.x >= config_.SCREN_WIDTH - collisionRec_.width ||
      collisionRec_.x <= 0) {
    speedX_ = -1 * speedX_;
    color_ = GetRandomColor();
  }

  if (collisionRec_.y >= config_.SCREEN_HEIGHT - collisionRec_.height ||
      collisionRec_.y <= 0) {
    speedY_ = -1 * speedY_;
    color_ = GetRandomColor();
  }
}

void DvdScreensaver::render() {
  DrawTexturePro(texture_, srcRec_, destRec_, origin_, 0, color_);

  if (config_.isDebugging()) {
    DrawRectangleLinesEx(collisionRec_, 1.f, YELLOW);
  }
}
