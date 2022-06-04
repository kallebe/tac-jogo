#include "Rect.hpp"

Rect::Rect() {
  x = 0.0;
  y = 0.0;
  w = 0.0;
  h = 0.0;
}

Rect::Rect(float x, float y, float w, float h) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

bool Rect::Contains(float x, float y) {
  bool xInRange = x >= this->x && x <= (this->x + this->w);
  bool yInRange = y >= this->y && y <= (this->y + this->h);
  
  return xInRange && yInRange;
}

float Rect::GetMiddleX() {
  return x + w/2;
}

float Rect::GetMiddleY() {
  return y + h/2;
}
