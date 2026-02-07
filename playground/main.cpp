#include "src/config.h"
#include "src/menu.h"
#include <cstdio>
#include <raylib.h>

int main() {
  // I had a bug here, calling instance even though the code there was correct,
  // in here without the & meant that I was making a copy of Config instead of
  // using the existing reference
  Config &config = Config::instance();

  InitWindow(config.SCREEN_WIDTH, config.SCREEN_HEIGHT, "Personal Playground");

  SetTargetFPS(60);

  Menu menu;

  SetExitKey(0);
  // Main game loop
  while (!WindowShouldClose()) {

    // event handler
    if (IsKeyPressed(KEY_D)) {
      config.setDebugging(!config.isDebugging());
    }

    menu.update();

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);

    menu.render();

    // printf("%f\n", GetFrameTime());
    EndDrawing();
  }

  // De-Initialization
  CloseWindow();

  return 0;
}
