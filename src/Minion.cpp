#include "Minion.hpp"

#include "Alien.hpp"
#include "Bullet.hpp"
#include "Camera.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include <math.h>

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
  // Sprite
  Sprite *sp = new Sprite(associated, "assets/img/minion.png");
  
  float scale = 1.0 + (rand() % 6)/10.0;
  sp->SetScale(scale, scale);

  associated.angleDeg = arcOffsetDeg;
  associated.AddComponent(sp);

  // Collider
  Collider *col = new Collider(associated, { scale, scale });
  associated.AddComponent(col);

  this->alienCenter = alienCenter;
  this->arc         = arcOffsetDeg;
}

void Minion::Start() {
  shared_ptr<GameObject> alienCenterPtr = alienCenter.lock();

  if (!alienCenterPtr) {
    associated.RequestDelete();
    return;
  }

  associated.box.x = cos(arc * PI / 180) * RAIO_CIRCULO + alienCenterPtr->box.x + alienCenterPtr->box.w/2 - associated.box.w/2;
  associated.box.y = sin(arc * PI / 180) * RAIO_CIRCULO + alienCenterPtr->box.y + alienCenterPtr->box.h/2 - associated.box.h/2;
}

void Minion::Update(float dt) {
  arc += DESLOCAMENTO_ARCO;
  shared_ptr<GameObject> alienCenterPtr = alienCenter.lock();

  if (!alienCenterPtr) {
    associated.RequestDelete();
    return;
  }

  associated.box.x = cos(arc * PI / 180) * RAIO_CIRCULO + alienCenterPtr->box.x + alienCenterPtr->box.w/2 - associated.box.w/2;
  associated.box.y = sin(arc * PI / 180) * RAIO_CIRCULO + alienCenterPtr->box.y + alienCenterPtr->box.h/2 - associated.box.h/2;

  associated.angleDeg += DESLOCAMENTO_ARCO;
}

bool Minion::Is(string type) {
  return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
  Game &game = Game::GetInstance();
  Camera &camera = Camera::GetInstance();
  GameObject *bulletGo = new GameObject();

  float angle = atan2(target.y + camera.pos.y - associated.box.GetMiddleY(), target.x + camera.pos.x - associated.box.GetMiddleX());

  bulletGo->box.x = this->associated.box.GetMiddleX();
  bulletGo->box.y = this->associated.box.GetMiddleY();

  Bullet *bullet = new Bullet(*bulletGo, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DISTANCE, "assets/img/minionbullet2.png", 3, 2000000.0, true);
  bulletGo->AddComponent(bullet);

  game.GetState().AddObject(bulletGo);
}

void Minion::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet*) other.GetComponent("Bullet");

    if (bullet->targetsPlayer)
      return;

    Game &game = Game::GetInstance();
    Alien *alien = (Alien*) alienCenter.lock()->GetComponent("Alien");

    alien->RemoveMinion(game.GetState().GetObjectPtr(&associated));

    associated.RequestDelete();
  }
}
