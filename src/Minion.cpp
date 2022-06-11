#include "Minion.hpp"
#include "Sprite.hpp"
#include <math.h>

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
  Sprite *sp = new Sprite(associated, "assets/img/minion.png");
  associated.AddComponent(sp);

  this->alienCenter = alienCenter;
  this->arc         = arcOffsetDeg;
}

void Minion::Start() {
  shared_ptr<GameObject> alienCenterPtr = alienCenter.lock();

  if (!alienCenterPtr) {
    associated.RequestDelete();
    return;
  }

  associated.box.x = cos(arc * PI / 180) * RAIO_CIRCULO + alienCenterPtr->box.x + alienCenterPtr->box.w/2;
  associated.box.y = sin(arc * PI / 180) * RAIO_CIRCULO + alienCenterPtr->box.y + alienCenterPtr->box.h/2;
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
}

bool Minion::Is(string type) {
  return type == "Minion";
}

void Minion::Shoot(Vec2 target) {

}

