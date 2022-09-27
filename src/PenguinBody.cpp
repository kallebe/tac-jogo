#include "PenguinBody.hpp"
#include "PenguinCannon.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <math.h>

PenguinBody::PenguinBody(GameObject &associated) : Component(associated) {
  // Sprite
  Sprite *sp = new Sprite(associated, "assets/img/penguin.png");
  associated.AddComponent(sp);

  // Collider
  Collider *col = new Collider(associated);
  associated.AddComponent(col);

  speed.x     = 0.0;
  speed.y     = 0.0;
  pos.x       = associated.box.x;
  pos.y       = associated.box.y;
  linearSpeed = 0.0;
  hp          = PENGUIN_HP;
  angle       = 0;
  player      = this;
}

PenguinBody::~PenguinBody() {
  player = nullptr;
}

void PenguinBody::Start() {
  Game &game = Game::GetInstance();
  weak_ptr<GameObject> pbody = game.GetState().GetObjectPtr(&associated);

  GameObject *pcGo = new GameObject();

  PenguinCannon *penguinCannon = new PenguinCannon(*pcGo, pbody);
  pcGo->AddComponent(penguinCannon);

  game.GetState().AddObject(pcGo);

  pcannon = game.GetState().GetObjectPtr(pcGo);

  Camera &camera = Camera::GetInstance();
  // camera.Follow(&associated);
}

void PenguinBody::Update(float dt) {
  InputManager &input = InputManager::GetInstance();

  if (input.IsKeyDown(FOWARD_W_KEY)) {
    speed.x = min(PENGUIN_ACCELERATION * abs(cos(angle * M_PI / 180)) + speed.x, MAX_PENGUIN_SPEED);
    speed.y = min(PENGUIN_ACCELERATION * abs(sin(angle * M_PI / 180)) + speed.y, MAX_PENGUIN_SPEED);
  }
  else if (input.IsKeyDown(BACKWARD_S_KEY)) {
    speed.x = max(speed.x - (PENGUIN_ACCELERATION * abs(cos(angle * M_PI / 180))), 0.0);
    speed.y = max(speed.y - (PENGUIN_ACCELERATION * abs(sin(angle * M_PI / 180))), 0.0);
  }
  else if (input.IsKeyDown(CLOCKWISE_D_KEY)) {
    angle += PENGUIN_ANGULAR_SPEED * dt;
    associated.angleDeg = angle;
  }
  else if (input.IsKeyDown(COUNTERCLOCKWISE_A_KEY)) {
    angle -= PENGUIN_ANGULAR_SPEED * dt;
    associated.angleDeg = angle;
  }

  // Atualiza posição
  pos.x += speed.x * cos(angle * M_PI / 180) * dt;
  pos.y += speed.y * sin(angle * M_PI / 180) * dt;

  Camera &camera = Camera::GetInstance();

  associated.box.x = pos.x + camera.pos.x - associated.box.w/2;
  associated.box.y = pos.y + camera.pos.y - associated.box.h/2;
}

void PenguinBody::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") != nullptr) {
    Camera &camera = Camera::GetInstance();
    Bullet *bullet = (Bullet*) other.GetComponent("Bullet");

    if (!bullet->targetsPlayer)
      return;

    hp -= bullet->GetDamage();

    // Deleção por hp
    if (hp <= 0) {
      camera.Unfollow();
      pcannon.lock()->RequestDelete();
      associated.RequestDelete();
    }
  }
}

void PenguinBody::Render() {
}

bool PenguinBody::Is(string type) {
  return type == "PenguinBody";
}
