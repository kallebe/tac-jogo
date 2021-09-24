#include "Face.hpp"
#include "Sound.hpp"

Face::Face(GameObject& associated) : Component(associated) {
  hitpoints = 30;
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
