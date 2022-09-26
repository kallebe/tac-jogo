#include "Collider.hpp"
#include <math.h>

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated) {
  this->scale = scale;
  this->offset = offset;
}

void Collider::Update(float dt) {
  this->box = associated.box;
  this->box.w *= scale.x;
  this->box.h *= scale.y;
  this->box.x  = associated.box.GetMiddleX() - this->box.w/2 + this->offset.x * cos(associated.angleDeg * M_PI / 180);
  this->box.y *= associated.box.GetMiddleY() - this->box.h/2 + this->offset.y * sin(associated.angleDeg * M_PI / 180);
}

void Collider::Render() {}

bool Collider::Is(string type) {
  return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}
