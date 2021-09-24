#include "GameObject.hpp"
#include "Component.hpp"

GameObject::GameObject() {
  isDead = false;
}

GameObject::~GameObject() {
  for (int i = components.size() - 1; i >= 0; i--)
    components.erase(components.begin() + i);
  components.clear();
}

void GameObject::Update(float dt) {
  for (uint i = 0; i < components.size(); i++)
    components[i]->Update(dt);
}

void GameObject::Render() {
  for (uint i = 0; i < components.size(); i++)
    components[i]->Render();
}

bool GameObject::IsDead() {
  return isDead;
}

void GameObject::RequestDelete() {
  isDead = true;
}

void GameObject::AddComponent(Component *component) {
  components.emplace_back(component);
}

void GameObject::RemoveComponent(Component *component) {
  for (uint i = 0; i < components.size(); i++)
    if (components[i].get() == component)
      components.erase(components.begin() + i);
}

Component* GameObject::GetComponent(string type) {
  for (uint i = 0; i < components.size(); i++) {
    if (components[i]->Is(type))
      return components[i].get();
  }

  return nullptr;
}
