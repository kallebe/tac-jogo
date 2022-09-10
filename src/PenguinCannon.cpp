#include "PenguinCannon.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Sprite.hpp"
#include "InputManager.hpp"

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component(associated) {
  Sprite *sp = new Sprite(associated, "assets/img/cubngun.png");
  associated.AddComponent(sp);

  pbody = penguinBody;
  angle = 0;
}

void PenguinCannon::Update(float dt) {
  shared_ptr<GameObject> pbodyPtr = pbody.lock();

  if (!pbodyPtr) {
    associated.RequestDelete();
    return;
  }

  associated.box.x = pbodyPtr->box.GetMiddleX() - associated.box.w/2;
  associated.box.y = pbodyPtr->box.GetMiddleY() - associated.box.h/2;

  InputManager &input = InputManager::GetInstance();
  Camera &camera = Camera::GetInstance();

  angle = atan2(input.GetMouseY() + camera.pos.y - associated.box.GetMiddleY(), input.GetMouseX() + camera.pos.x - associated.box.GetMiddleX());
  associated.angleDeg = angle * 180 / M_PI;

  if (input.MousePress(LEFT_MOUSE_BUTTON)) {
    Shoot();
  }
}

void PenguinCannon::Render() {
}

bool PenguinCannon::Is(string type) {
  return type == "PenguinCannon";
}

void PenguinCannon::Shoot() {
  Game &game = Game::GetInstance();
  GameObject *bulletGo = new GameObject();

  bulletGo->box.x = associated.box.x + associated.box.w * (0.5 * cos(angle) + 0.5);
  bulletGo->box.y = associated.box.GetMiddleY() + associated.box.w * 0.5 * sin(angle);

  Bullet *bullet = new Bullet(*bulletGo, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DISTANCE, "assets/img/minionbullet2.png", 3, 2000000.0);
  bulletGo->AddComponent(bullet);

  game.GetState().AddObject(bulletGo);
}

