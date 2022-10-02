#include "State.hpp"

State::State() {
  quitRequested = false;
  popRequested  = false;
  started       = false;
}

State::~State() {
  objectArray.clear();
}

weak_ptr<GameObject> State::AddObject(GameObject *go) {
  shared_ptr<GameObject> ptr(go);

  objectArray.push_back(ptr);

  if (go->started)
    go->Start();
  
  weak_ptr<GameObject> weak_pointer = ptr;
  return weak_pointer;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
  weak_ptr<GameObject> weak_pointer;

  for (uint i = 0; i < objectArray.size(); i++) {
    if (objectArray[i].get() == go) {
      weak_pointer = objectArray[i];
      return weak_pointer;
    }
  }

  return weak_pointer;
}

bool State::QuitRequested() {
  return quitRequested;
}

bool State::PopRequested() {
  return popRequested;
}

void State::StartArray() {
  for (uint i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Start();
  }
}

void State::UpdateArray(float dt) {
  for (uint i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Update(dt);
  }
}

void State::RenderArray() {
  for (uint i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Render();
  }
}
