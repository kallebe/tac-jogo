#include "Face.hpp"
#include "Sound.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Camera.hpp"

Face::Face(GameObject& associated) : Component(associated) {
  hitpoints = 30;
  pos.x = associated.box.x;
  pos.y = associated.box.y;
}

void Face::Damage(int damage) {
  hitpoints -= damage;

  if (hitpoints <= 0) {
    Sound *sound = reinterpret_cast<Sound*>(associated.GetComponent("Sound"));

    if (sound != nullptr) {
      sound->Play();
      
      while (Mix_Playing(sound->GetChannel()));
    }
    
    associated.RequestDelete();
  }
}

bool Face::Is(string type) {
  return type == "Face";
}

void Face::Update(float dt) {
  InputManager &input = InputManager::GetInstance();

  if (input.MousePress(LEFT_MOUSE_BUTTON)) {
    if (associated.box.Contains((float) input.GetMouseX(), (float) input.GetMouseY())) {
      Damage(std::rand() % 10 + 10);  // Aplica dano
    }
  }
}

void Face::Render() {
  Camera &camera = Camera::GetInstance();

  associated.box.x = pos.x + camera.pos.x;
  associated.box.y = pos.y + camera.pos.y;
}
