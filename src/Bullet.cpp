#include "Bullet.hpp"

#include "Camera.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include <math.h>

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer) : Component(associated) {
  // Sprite
  Sprite *sp = new Sprite(associated, sprite, frameCount, frameTime);
  associated.AddComponent(sp);

  associated.angleDeg = angle * 180 / M_PI;

  float colisionScale = 1.0 / frameCount;
  associated.box.x -= colisionScale * associated.box.w / 2;
  associated.box.y -= associated.box.h / 2;

  Camera &camera = Camera::GetInstance();
  pos.x = associated.box.x - camera.pos.x;
  pos.y = associated.box.y - camera.pos.y;

  // Collider
  Vec2 colOffset = { 0, 0};
  colOffset.x = -associated.box.w/2 + (colisionScale * associated.box.w/2);

  Collider *col = new Collider(associated, { colisionScale, 1 }, colOffset);
  associated.AddComponent(col);

  this->speed.x = speed * cos(angle);
  this->speed.y = speed * sin(angle);

  this->targetsPlayer = targetsPlayer;
  this->distanceLeft = maxDistance;
  this->damage       = damage;
}

void Bullet::Update(float dt) {
  Vec2 displacement = speed * dt;
  Camera &camera = Camera::GetInstance();

  pos = pos + displacement;

  this->associated.box.x = pos.x + displacement.x + camera.pos.x;
  this->associated.box.y = pos.y + displacement.y + camera.pos.y;
  this->distanceLeft -= displacement.Size();

  if (distanceLeft <= 0)
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
