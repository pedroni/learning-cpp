#include <cstdio>
#include <raylib.h>

using namespace std;

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "DVD Screensaver");

  SetTargetFPS(60);

  int rectWidth = 50;
  int rectHeight = 50;

  int posX = 0;
  int posY = 0;

  int speedX = 2;
  int speedY = 2;

  Texture2D dvd = LoadTexture("./dvd.png");

  // Main game loop
  while (!WindowShouldClose()) {

    // Update
    posX += speedX;
    posY += speedY;

    // remember to always add \n after printing so that the buffer gets flushed
    // printf("x(%d) y(%d)\n", posX, posY);

    if (posX >= screenWidth - rectWidth || posX <= 0) {
      speedX = -1 * speedX;
    }

    if (posY >= screenHeight - rectHeight || posY <= 0) {
      speedY = -1 * speedY;
    }

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(dvd,  posX,  posY,  WHITE);

    // DrawRectangle(posX, posY, rectWidth, rectHeight, WHITE);

    EndDrawing();
  }

  // De-Initialization
  CloseWindow();

  return 0;
}
