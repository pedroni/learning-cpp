#pragma once

#include "RecEntity.h"
#include "config.h"
#include "entity.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>
#include <vector>

class Pong : public Entity {
  const float BORDER_SIZE = 5;

  const float PLAYER_WIDTH = 10;
  const float PLAYER_HEIGHT = 60;
  const float PLAYER_SPEED = 8;

  const float BALL_SIZE = 10;
  const float BALL_SPEED = 4;

  const float SCORE_SIZE = 20;
  const float STATE_SIZE = 40;

  Config &config_;

  // used to identify when the ball hits each side
  RecEntity topBorderRec_;
  RecEntity bottomBorderRec_;
  RecEntity leftBorderRec_;
  RecEntity rightBorderRec_;

  RecEntity playerRec_;
  float playerSpeed = 0;

  RecEntity enemyRec_;
  float enemySpeed = PLAYER_SPEED * 1.2;

  RecEntity ballRec_;
  float ballSpeedX = BALL_SPEED;
  float ballSpeedY = BALL_SPEED;

  // vector cannot construct Entity therefore we need a pointer of Entity
  std::vector<Entity *> entities_;

  int playerScore = 0;
  int enemyScore = 0;

  void initializeRecs_() {
    topBorderRec_.width = config_.SCREEN_WIDTH;
    topBorderRec_.height = BORDER_SIZE;

    bottomBorderRec_.y = config_.SCREEN_HEIGHT - BORDER_SIZE;
    bottomBorderRec_.width = config_.SCREEN_WIDTH;
    bottomBorderRec_.height = BORDER_SIZE;

    leftBorderRec_.x = 0;
    leftBorderRec_.y = 0;
    leftBorderRec_.width = BORDER_SIZE;
    leftBorderRec_.height = config_.SCREEN_HEIGHT;

    rightBorderRec_.x = config_.SCREEN_WIDTH - BORDER_SIZE;
    rightBorderRec_.y = 0;
    rightBorderRec_.width = BORDER_SIZE;
    rightBorderRec_.height = config_.SCREEN_HEIGHT;

    resetBall_();

    playerRec_.x = BORDER_SIZE * 2;
    playerRec_.y = 0;
    playerRec_.width = PLAYER_WIDTH;
    playerRec_.height = PLAYER_HEIGHT;
    playerRec_.color = BLUE;

    enemyRec_.x = config_.SCREEN_WIDTH - BORDER_SIZE * 2 - PLAYER_WIDTH;
    enemyRec_.y = 0;
    enemyRec_.width = PLAYER_WIDTH;
    enemyRec_.height = PLAYER_HEIGHT;
    enemyRec_.color = RED;
  }

  void resetBall_() {
    ballRec_.x = (config_.SCREEN_WIDTH / 2) - (BALL_SIZE / 2);
    ballRec_.y = (config_.SCREEN_HEIGHT / 2) - (BALL_SIZE / 2);
    ballRec_.width = BALL_SIZE;
    ballRec_.height = BALL_SIZE;
    ballRec_.color = WHITE;
  }

public:
  bool paused = false;

  Pong() : config_(Config::instance()) {
    initializeRecs_();

    entities_.push_back(&topBorderRec_);
    entities_.push_back(&bottomBorderRec_);
    entities_.push_back(&leftBorderRec_);
    entities_.push_back(&rightBorderRec_);
    entities_.push_back(&ballRec_);
    entities_.push_back(&playerRec_);
    entities_.push_back(&enemyRec_);
  }

  void checkCollisions() {
    // bounce the ball off left and right on X axis always, however
    if (CheckCollisionRecs(ballRec_.getRec(), playerRec_.getRec())) {
      ballSpeedX *= -1;
    }

    if (CheckCollisionRecs(ballRec_.getRec(), enemyRec_.getRec())) {
      ballSpeedX *= -1;
    }

    if (CheckCollisionRecs(ballRec_.getRec(), topBorderRec_.getRec()) ||
        CheckCollisionRecs(ballRec_.getRec(), bottomBorderRec_.getRec())) {
      // bounce of top and bottom
      ballSpeedY *= -1;
    }

    if (CheckCollisionRecs(ballRec_.getRec(), rightBorderRec_.getRec())) {
      resetBall_();
      paused = true;
      playerScore++;
    }

    if (CheckCollisionRecs(ballRec_.getRec(), leftBorderRec_.getRec())) {
      resetBall_();
      paused = true;
      enemyScore++;
    }
  }

  void update() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
      paused = !paused;
    }

    if (paused) {
      return;
    }

    checkCollisions();

    // player handling
    if (IsKeyDown(KEY_DOWN)) {
      playerRec_.y += PLAYER_SPEED;
    } else if (IsKeyDown(KEY_UP)) {
      playerRec_.y -= PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_R)) {
      // restart the game;
      initializeRecs_();
    }

    // basic ai just goes back and forth
    if (enemyRec_.y < 0 ||
        enemyRec_.y > config_.SCREEN_HEIGHT - enemyRec_.height) {
      enemySpeed *= -1;
    }

    enemyRec_.y += enemySpeed;

    if (playerRec_.y < 0) {
      playerRec_.y = 0;
    }

    if (playerRec_.y > config_.SCREEN_HEIGHT - playerRec_.height) {
      playerRec_.y = config_.SCREEN_HEIGHT - playerRec_.height;
    }

    // ball handling
    ballRec_.x += ballSpeedX;
    ballRec_.y += ballSpeedY;
  }

  void render() {
    // auto & to avoid copying the pointers, small optimaztion, this is a
    // reference to a pointer

    // for (auto &entity : entities_) {
    for (Entity *&entity : entities_) {
      entity->render();
    }

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d x %d", playerScore, enemyScore);
    float width = MeasureText(buffer, SCORE_SIZE);
    DrawText(
        buffer, (config_.SCREEN_WIDTH / 2) - (width / 2), 10, SCORE_SIZE, WHITE
    );

    if (paused) {
      char paused[20] = "Paused";
      width = MeasureText(paused, STATE_SIZE);
      DrawText(
          paused,
          (config_.SCREEN_WIDTH / 2) - (width / 2),
          40,
          STATE_SIZE,
          YELLOW
      );
    }
  }
};
