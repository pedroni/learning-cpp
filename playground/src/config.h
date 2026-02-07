#pragma once
#include <cstdio>

class Config {
private:
  bool _debugging = false;
  Config() { printf("Config initialized.\n"); }

public:
  const float SCREEN_WIDTH = 800;
  const float SCREEN_HEIGHT = 450;

  // Scott Meyers Singleton pattern
  static Config &instance() {
    static Config instance;
    return instance;
  };

  // prevent accidental mistakes
  Config(const Config &) = delete;
  Config(Config &&) = delete;
  Config &operator=(Config &&) = delete;
  Config &operator=(const Config &) = delete;

  void setDebugging(bool debugging) {
    _debugging = debugging;

    printf("D is called\n");
  }
  bool isDebugging() { return _debugging; }
};
