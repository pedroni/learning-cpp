#pragma once

#include "config.h"
#include "dvd-screensaver.h"
#include "entity.h"
#include "pong.h"
#include "raylib.h"
#include <set>
#include <string>
#include <vector>

struct MenuOption {
  std::string name;
  Entity *app;
};

class Menu {
  const unsigned short FONT_SIZE = 20;

  std::vector<MenuOption> options_;
  Config &config_;
  short hoveringAction_ = -1;
  Entity *activeApp_ = nullptr;

public:
  Menu() : config_(Config::instance()) {
    MenuOption dvd;
    dvd.name = "DVD Screensaver";
    dvd.app = new DvdScreensaver();

    options_.push_back(dvd);
  }

  void update() {
    if (activeApp_ != nullptr) {
      if (IsKeyPressed(KEY_ESCAPE)) {
        activeApp_ = nullptr;
        return;
      }

      activeApp_->update();
      return;
    }

    if (IsKeyPressed(KEY_DOWN)) {
      hoveringAction_++;
    } else if (IsKeyPressed(KEY_UP)) {
      hoveringAction_--;
    }

    if (hoveringAction_ < 0) {
      hoveringAction_ = -1;
    } else if (hoveringAction_ > options_.size() - 1) {
      hoveringAction_ = 0;
    }

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
      if (hoveringAction_ != -1) {
        activeApp_ = options_.at(hoveringAction_).app;
      }
    }
  }

  void render() {
    if (activeApp_ != nullptr) {
      activeApp_->render();
      return;
    }

    int menuWidth = MeasureText("Menu", FONT_SIZE);
    DrawText("Menu", (config_.SCREEN_WIDTH / 2) - ((float)menuWidth / 2), 40,
             FONT_SIZE, hoveringAction_ == -1 ? YELLOW : WHITE);

    for (size_t i = 0; i < options_.size(); i++) {
      MenuOption option = options_[i];

      int nameWidth = MeasureText(option.name.c_str(), FONT_SIZE);
      DrawText(option.name.c_str(),
               (config_.SCREEN_WIDTH / 2) - ((float)nameWidth / 2),
               (FONT_SIZE + 10) * (i + 1) + 80, FONT_SIZE,
               hoveringAction_ == i ? YELLOW : WHITE);
    }

    return;
  }
};
