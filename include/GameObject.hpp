#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Rect.hpp"
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

class Component;

class GameObject {
  private:
    vector<unique_ptr<Component>> components;
    bool isDead;
  
  public:
    Rect box;

    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component *component);
    void RemoveComponent(Component *component);
    Component* GetComponent(string type);
};

#endif
