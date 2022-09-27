#include "Bullet.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include <math.h>
#include <iostream>

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer) : Component(associated) {
  // Sprite
  Sprite *sp = new Sprite(associated, sprite, frameCount, frameTime);
  associated.AddComponent(sp);

  associated.angleDeg = angle * 180 / M_PI;
  associated.box.y -= cos(angle) * associated.box.h / 2;
  associated.box.y -= sin(angle) * associated.box.w / 2;

  // Collider
  Collider *col = new Collider(associated, { 0.3, 1 }, { -associated.box.w/3, 0 });
  associated.AddComponent(col);

  this->speed.x = speed * cos(angle);
  this->speed.y = speed * sin(angle);

  this->targetsPlayer = targetsPlayer;
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

void Bullet::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") == nullptr) {
    if (((other.GetComponent("Alien") || other.GetComponent("Minion")) && !targetsPlayer) || ((other.GetComponent("PenguinCannon") || other.GetComponent("PenguinBody")) && targetsPlayer))
      associated.RequestDelete();
  }
}
