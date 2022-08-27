#include "Bullet.hpp"
#include "Sprite.hpp"
#include <math.h>
#include <iostream>

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime) : Component(associated) {
  Sprite *sp = new Sprite(associated, sprite, frameCount, frameTime);
  associated.AddComponent(sp);

  associated.angleDeg = angle * 180 / M_PI;

  this->speed.x = speed * cos(angle);
  this->speed.y = speed * sin(angle);

  this->distanceLeft = maxDistance;
  this->damage       = damage;
}

void Bullet::Update(float dt) {
  Vec2 displacement = speed * dt;

  this->associated.box.x += displacement.x;
  this->associated.box.y += displacement.y;
  this->distanceLeft -= displacement.Size();

  if (this->distanceLeft <= 0)
    associated.RequestDelete();
}

bool Bullet::Is(string type) {
  return type == "Bullet";
}

int Bullet::GetDamage() {
  return damage;
}

