#include "Vec2.hpp"
#include <math.h>

Vec2::Vec2() {
  x = 0.0;
  y = 0.0;
}

Vec2::Vec2(float x, float y) {
  this->x = x;
  this->y = y;
}

Vec2 Vec2::GetRotated(float deg) {
  Vec2 rotated;

  rotated.x = x * cos(deg) - y * sin(deg);
  rotated.y = y * cos(deg) + x * sin(deg);

  return rotated;
}

Vec2 Vec2::operator+(Vec2 const &vector) {
  Vec2 sum;

  sum.x = this->x + vector.x;
  sum.y = this->y + vector.y;

  return sum;
}
