#include "../include/Game.hpp"
#include "Face.hpp"
#include "Sound.hpp"
#include "TileMap.hpp"
#include "Vec2.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "CameraFollower.hpp"
#include "Alien.hpp"

State::State() : music("assets/audio/stageState.ogg") {
  quitRequested = false;
  started       = false;

	// Background
  GameObject *go = new GameObject();
	go->box.x = 0;
	go->box.y = 0;

  bg = new Sprite(*go);
  go->AddComponent(bg);

  objectArray.emplace_back(go);

	// TileMap
	GameObject *tm = new GameObject();
	tm->box.x = 0;
	tm->box.y = 0;

	TileSet *tileset = new TileSet(64, 64, "assets/img/tileset.png");
	TileMap *tilemap = new TileMap(*tm, "assets/map/tileMap.txt", tileset);
	tm->AddComponent(tilemap);

  CameraFollower *cf = new CameraFollower(*tm);
  tm->AddComponent(cf);

	objectArray.emplace_back(tm);

  // Alien
  GameObject *alienObj = new GameObject();
  alienObj->box.x = 512;
  alienObj->box.y = 300;

  Alien *alien = new Alien(*alienObj, 5);
  alienObj->AddComponent(alien);

  objectArray.emplace_back(alienObj);

  if (music.IsOpen())
    music.Play();
}

State::~State() {
  objectArray.clear();
}

void State::LoadAssets() {
  bg->Open("assets/img/ocean.jpg");
  bg->SetClip(0, 0, 1024, 600);
}

void State::Start() {
  LoadAssets();

  for (uint i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Start();
  }

  started = true;
}

void State::Update(float dt) {
  // Input();
	InputManager &input = InputManager::GetInstance();
  Camera &camera      = Camera::GetInstance();

	quitRequested = input.KeyPress(ESCAPE_KEY) || input.QuitRequested();

  // Adiciona Face
	// if (input.KeyPress(SPACE_KEY))
	// 	AddObject(input.GetMouseX(), input.GetMouseY());
  
  // Atualiza posição da Camera
  camera.Update(dt);

  for (uint i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Update(dt);
  }

  for (uint i = 0; i < objectArray.size(); i++) {
    if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin() + i);
    }
  }
}

void State::Render() {
  for (uint i = 0; i < objectArray.size(); i++)
    objectArray[i]->Render();
}

bool State::QuitRequested() {
  return quitRequested;
}

void State::Run() {
  Game &game = Game::GetInstance();
	InputManager &input = InputManager::GetInstance();

  while (!quitRequested) {
    float dt = game.GetDeltaTime();
	  input.Update();

    Update(dt);
    Render();
    SDL_RenderPresent(game.GetRenderer());
    SDL_Delay(33);
  }
}

// void State::AddObject(int mouseX, int mouseY) {
//   GameObject *go      = new GameObject();
//   Camera     &camera  = Camera::GetInstance();

//   Sprite *enemy = new Sprite(*go, "assets/img/penguinface.png");
//   go->AddComponent(enemy);

//   go->box.x = mouseX - camera.pos.x + enemy->GetWidth()/2;
//   go->box.y = mouseY - camera.pos.y + enemy->GetHeight()/2;

//   Sound *sound = new Sound(*go, "assets/audio/boom.wav");
//   go->AddComponent(sound);

//   Face *face = new Face(*go);
//   go->AddComponent(face);

//   objectArray.emplace_back(go);
// }

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
