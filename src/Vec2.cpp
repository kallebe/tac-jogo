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

Vec2 Vec2::Rotate(float rad) {
  Vec2 rotated;

  rotated.x = x * cos(rad) - y * sin(rad);
  rotated.y = y * cos(rad) + x * sin(rad);

  return rotated;
}

float Vec2::Size() {
  return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2 Vec2::operator+(Vec2 const &vector) {
  return Vec2(x + vector.x, y + vector.y);
}

Vec2 Vec2::operator-(Vec2 const &vector) {
  return Vec2(x - vector.x, y - vector.y);
}

Vec2 Vec2::operator+(Rect rect) {
  return Vec2(x + rect.x, y + rect.y);
}

Vec2 Vec2::operator-(Rect rect) {
  return Vec2(x - rect.x, y - rect.y);
}

Vec2 Vec2::operator*(const float rhs) const {
   return Vec2(x * rhs, y * rhs);
}
