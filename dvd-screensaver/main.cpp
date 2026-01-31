#include <cstdio>
#include <raylib.h>

Color GetRandomColor() {
  Color color;
  color.r = GetRandomValue(0, 255);
  color.g = GetRandomValue(0, 255);
  color.b = GetRandomValue(0, 255);
  color.a = 255;
  return color;
}

int main() {
  const int SCREN_WIDTH = 800;
  const int SCREEN_HEIGHT = 450;
  const float INITIAL_SPEED = 2;

  InitWindow(SCREN_WIDTH, SCREEN_HEIGHT, "DVD Screensaver");

  SetTargetFPS(60);

  int speedX = 2;
  int speedY = 2;

  int acceleration = 1;

  Texture2D dvd = LoadTexture("./dvd.png");

  Rectangle dvdSrc;
  dvdSrc.x = 0;
  dvdSrc.y = 0;
  dvdSrc.width = (float)dvd.width;
  dvdSrc.height = (float)dvd.height;

  Rectangle dvdDest;
  dvdDest.width = 50.;
  dvdDest.height = (50.f * dvd.height) / dvd.width;

  Rectangle dvdCollision;

  dvdCollision.width = 43;
  dvdCollision.height = 22;
  dvdCollision.x = 0;
  dvdCollision.y = 0;

  Vector2 dvdOrigin;
  dvdOrigin.x = 0;
  dvdOrigin.y = 0;

  bool debugging = false;

  Color dvdColor = WHITE;

  // Main game loop
  while (!WindowShouldClose()) {

    // event handler
    if (IsKeyPressed(KEY_D)) {
      debugging = !debugging;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      acceleration += 1;
    } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
      acceleration -= 1;
    }

    // Update
    dvdCollision.x += speedX * acceleration;
    dvdCollision.y += speedY * acceleration;

    dvdDest.x = dvdCollision.x - 5;
    dvdDest.y = dvdCollision.y - 15;

    // remember to always add \n after printing so that the buffer gets flushed
    if (debugging) {
      printf("x(%f) y(%f)\n", dvdCollision.x, dvdCollision.y);
    }

    if (dvdCollision.x >= SCREN_WIDTH - dvdCollision.width ||
        dvdCollision.x <= 0) {
      speedX = -1 * speedX;
      dvdColor = GetRandomColor();
    }

    if (dvdCollision.y >= SCREEN_HEIGHT - dvdCollision.height ||
        dvdCollision.y <= 0) {
      speedY = -1 * speedY;
      dvdColor = GetRandomColor();
    }

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(dvd, dvdSrc, dvdDest, dvdOrigin, 0, dvdColor);

    if (debugging) {
      DrawRectangleLinesEx(dvdCollision, 1.f, YELLOW);
    }

    EndDrawing();
  }

  // good practice to remember to free the resources
  UnloadTexture(dvd);

  // De-Initialization
  CloseWindow();

  return 0;
}
