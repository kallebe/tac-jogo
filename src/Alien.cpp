#include "Alien.hpp"

#include "Bullet.hpp"
#include "Camera.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "Minion.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include <math.h>
#include <iostream>

Alien::Alien(GameObject& associated, int numMinions) : Component(associated) {
  // Sprite
  Sprite *sp = new Sprite(associated, "assets/img/alien.png");
  associated.AddComponent(sp);

  // Collider
  Collider *col = new Collider(associated, { 0.6, 0.6 });
  associated.AddComponent(col);

  hp       = ALIEN_HP;
  nMinions = numMinions;
  speed.x  = 0.00004;
  speed.y  = 0.00004;
  pos.x    = associated.box.GetMiddleX();
  pos.y    = associated.box.GetMiddleY();
}

Alien::~Alien() {
  minionArray.clear();
}

void Alien::Start() {
  Game &game = Game::GetInstance();
  weak_ptr<GameObject> alienCenter = game.GetState().GetObjectPtr(&associated);

  if (!alienCenter.lock()) {
    return;
  }

  float darc = 360 / nMinions;

  for (int i = 0; i < nMinions; i++) {
    GameObject *minionGo = new GameObject();

    Minion *minion = new Minion(*minionGo, alienCenter, i * darc);
    minionGo->AddComponent(minion);

    minionArray.push_back(game.GetState().AddObject(minionGo));
  }
}

void Alien::Update(float dt) {
  InputManager &input = InputManager::GetInstance();
  // Verificando novas ações
  if (input.MousePress(LEFT_MOUSE_BUTTON) && minionArray.size()) {
    Action shoot = Action(Action::ActionType::SHOOT, input.GetMouseX(), input.GetMouseY());
    taskQueue.push(shoot);

  } else if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
    Action move = Action(Action::ActionType::MOVE, input.GetMouseX(), input.GetMouseY());
    taskQueue.push(move);
  }

  // Executar ações pendentes
  if (taskQueue.size()) {
    Action task = taskQueue.front();

    if (task.type == Action::ActionType::MOVE) {
      float angle = atan2(task.pos.y-pos.y, task.pos.x-pos.x);
      float dx = speed.x * cos(angle) * dt;
      float dy = speed.y * sin(angle) * dt;

      bool withinLimitsX = abs(pos.x - task.pos.x) < dx;
      bool withinLimitsY = abs(pos.y - task.pos.y) < dy;

      if (withinLimitsX || withinLimitsY) {
        pos.x = task.pos.x;
        pos.y = task.pos.y;

        taskQueue.pop();  // Finaliza tarefa

      } else {
        pos.x += dx;
        pos.y += dy;
      }
    }

    if (task.type == Action::ActionType::SHOOT) {
      Minion *minion = (Minion *) minionArray[rand() % minionArray.size()].lock().get()->GetComponent("Minion");
      
      minion->Shoot(task.pos);
      taskQueue.pop();
    }
  }

  // Girar lentamente
  associated.angleDeg -= DESLOCAMENTO_ARCO / 4;

  // Remover Alien por dano
  if (hp <= 0)
    associated.RequestDelete();

  if (associated.IsDead()) {
    Game &game = Game::GetInstance();
    GameObject *explosionGo = new GameObject();
    explosionGo->box.x = associated.box.x;
    explosionGo->box.y = associated.box.y;
    
    Sprite *explosion = new Sprite(*explosionGo, "assets/img/aliendeath.png", 4, 800000.0, 32.0);
    explosionGo->AddComponent(explosion);

    Sound *sound = new Sound(*explosionGo, "assets/audio/boom.wav");
    explosionGo->AddComponent(sound);

    if (sound != nullptr)
      sound->Play();

    game.GetState().AddObject(explosionGo);
  }
}

void Alien::Render() {
  Camera &camera = Camera::GetInstance();

  associated.box.x = pos.x + camera.pos.x - associated.box.w/2;
  associated.box.y = pos.y + camera.pos.y - associated.box.h/2;
}

bool Alien::Is(string type) {
  return type == "Alien";
}

void Alien::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet*) other.GetComponent("Bullet");

    if (bullet->targetsPlayer)
      return;

    hp -= bullet->GetDamage();
  }
}

void Alien::RemoveMinion(weak_ptr<GameObject> minion) {
  for (int i = minionArray.size() - 1; i >= 0; i--)
    if (minionArray[i].lock() == minion.lock())
      minionArray.erase(minionArray.begin() + i);
}

Alien::Action::Action::Action(ActionType type, float x, float y) {
  this->type  = type;
  pos.x       = x;
  pos.y       = y;
}
