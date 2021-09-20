#include "Face.hpp"
#include "Sound.hpp"

Face::Face(GameObject& associated) : Component(associated) {
  hitpoints = 30;
}

void Face::Damage(int damage) {
  hitpoints--;

  if (hitpoints <= 0) {
    Sound *sound = reinterpret_cast<Sound*>(associated.GetComponent("Sound"));

    if (sound)
      sound->Play();
    associated.RequestDelete();
  }
}

void Face::Update(float dt) {}

void Face::Render() {}

bool Face::Is(string type) {
  return type == "Face";
}
