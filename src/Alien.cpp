#include "Alien.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "InputManager.hpp"
#include <iostream>

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
  Sprite *sp = new Sprite(associated, "assets/img/alien.png");
  associated.AddComponent(sp);

  hp      = 30;
  speed.x = 0.00004;
  speed.y = 0.00004;
  // pos.x   = associated.box.x;
  // pos.y   = associated.box.y;
}

Alien::~Alien() {
  minionArray.clear();
}

void Alien::Start() {

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
      float dx = speed.x * dt;
      float dy = speed.y * dt;

      bool withinLimitsX = abs(associated.box.GetMiddleX() - task.pos.x) < dx;
      bool withinLimitsY = abs(associated.box.GetMiddleY() - task.pos.y) < dy;

      if (withinLimitsX && withinLimitsY) {
        associated.box.x = task.pos.x - associated.box.w/2;
        associated.box.y = task.pos.y - associated.box.h/2;

        taskQueue.pop();  // Finaliza tarefa

      } else {
        if (task.pos.x > associated.box.GetMiddleX() && !withinLimitsX)
          associated.box.x += dx;
        
        else if (task.pos.x < associated.box.GetMiddleX() && !withinLimitsX)
          associated.box.x -= dx;
        
        if (task.pos.y > associated.box.GetMiddleY() && !withinLimitsY)
          associated.box.y += dy;
        
        else if (task.pos.y < associated.box.GetMiddleY() && !withinLimitsY)
          associated.box.y -= dy;
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
//   Camera &camera = Camera::GetInstance();

//   associated.box.x = pos.x + camera.pos.x;
//   associated.box.y = pos.y + camera.pos.y;
}

bool Alien::Is(string type) {
  return type == "Alien";
}

Alien::Action::Action::Action(ActionType type, float x, float y) {
  this->type  = type;
  pos.x       = x;
  pos.y       = y;
}