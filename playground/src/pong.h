#pragma once

#include "config.h"
#include "entity.h"
#include "raylib.h"
#include "raymath.h"

class Pong : public Entity {
  const float BORDER_WIDTH = 5;

  const float PLAYER_WIDTH = 10;
  const float PLAYER_HEIGHT = 60;
  const float PLAYER_SPEED = 8;

  const float BALL_SIZE = 10;
  const float BALL_SPEED = 8;

  Config &config_;

  // used to identify when the ball hits each side
  Rectangle leftBorderRec_;
  Rectangle rightBorderRec_;

  Rectangle playerRec_;
  float playerSpeed = 0;

  Rectangle aiRec_;
  float aiSpeed = PLAYER_SPEED * 1.2;

  Rectangle ballRec_;
  float ballSpeed = BALL_SPEED;

public:
  Pong() : config_(Config::instance()) {
    leftBorderRec_.x = 0;
    leftBorderRec_.y = 0;
    leftBorderRec_.width = BORDER_WIDTH;
    leftBorderRec_.height = config_.SCREEN_HEIGHT;

    rightBorderRec_.x = config_.SCREEN_WIDTH - BORDER_WIDTH;
    rightBorderRec_.y = 0;
    rightBorderRec_.width = BORDER_WIDTH;
    rightBorderRec_.height = config_.SCREEN_HEIGHT;

    ballRec_.x = (config_.SCREEN_WIDTH / 2) - (BALL_SIZE / 2);
    ballRec_.y = (config_.SCREEN_HEIGHT / 2) - (BALL_SIZE / 2);

    ballRec_.width = BALL_SIZE;
    ballRec_.height = BALL_SIZE;

    playerRec_.x = BORDER_WIDTH * 2;
    playerRec_.y = 0;
    playerRec_.width = PLAYER_WIDTH;
    playerRec_.height = PLAYER_HEIGHT;

    aiRec_.x = config_.SCREEN_WIDTH - BORDER_WIDTH * 2 - PLAYER_WIDTH;
    aiRec_.y = 0;
    aiRec_.width = PLAYER_WIDTH;
    aiRec_.height = PLAYER_HEIGHT;
  }

  void update() {

    // TODO:: make ai, ball and player be an entity

    // basic ai just goes back and forth
    if (aiRec_.y < 0 || aiRec_.y > config_.SCREEN_HEIGHT - aiRec_.height) {
      aiSpeed *= -1;
    }

    aiRec_.y += aiSpeed;

    // player handling
    if (IsKeyDown(KEY_DOWN)) {
      playerRec_.y += PLAYER_SPEED;
    } else if (IsKeyDown(KEY_UP)) {
      playerRec_.y -= PLAYER_SPEED;
    }

    if (playerRec_.y < 0) {
      playerRec_.y = 0;
    }

    if (playerRec_.y > config_.SCREEN_HEIGHT - playerRec_.height) {
      playerRec_.y = config_.SCREEN_HEIGHT - playerRec_.height;
    }

    // ball handling
    ballRec_.x += ballSpeed;
    // to make it simple im boucing off the walls first
    // if (GetCollisionRec(ballRec_, rightBorderRec_))
  }

  void render() {
    DrawRectangle(leftBorderRec_.x, leftBorderRec_.y, leftBorderRec_.width,
                  leftBorderRec_.height, GRAY);
    DrawRectangle(rightBorderRec_.x, rightBorderRec_.y, rightBorderRec_.width,
                  rightBorderRec_.height, GRAY);

    DrawRectangle(playerRec_.x, playerRec_.y, playerRec_.width,
                  playerRec_.height, BLUE);
    DrawRectangle(aiRec_.x, aiRec_.y, aiRec_.width, aiRec_.height, RED);

    DrawRectangle(ballRec_.x, ballRec_.y, ballRec_.width, ballRec_.height,
                  WHITE);
  }
};
