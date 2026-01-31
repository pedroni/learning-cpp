#include "helpers.h"

Color GetRandomColor() {
  Color color;
  color.r = GetRandomValue(0, 255);
  color.g = GetRandomValue(0, 255);
  color.b = GetRandomValue(0, 255);
  color.a = 255;
  return color;
}
