#include "Alien.hpp"
#include "Minion.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include <math.h>
#include <iostream>

Alien::Alien(GameObject& associated, int numMinions) : Component(associated) {
  Sprite *sp = new Sprite(associated, "assets/img/alien.png");
  associated.AddComponent(sp);

  hp       = 30;
  nMinions = numMinions;
  speed.x  = 6;
  speed.y  = 6;
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
  if (input.MousePress(LEFT_MOUSE_BUTTON)) {
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
      float dx = speed.x * cos(angle);
      float dy = speed.y * sin(angle);

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
      taskQueue.pop();
    }
  }

  // Remover Alien por dano
  if (hp <= 0)
    associated.RequestDelete();
}

void Alien::Render() {
  Camera &camera = Camera::GetInstance();

  associated.box.x = pos.x + camera.pos.x - associated.box.w/2;
  associated.box.y = pos.y + camera.pos.y - associated.box.h/2;
}

bool Alien::Is(string type) {
  return type == "Alien";
}

Alien::Action::Action::Action(ActionType type, float x, float y) {
  this->type  = type;
  pos.x       = x;
  pos.y       = y;
}
