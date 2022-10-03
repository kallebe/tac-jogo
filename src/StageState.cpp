#include "StageState.hpp"

#include "Alien.hpp"
#include "Camera.hpp"
#include "CameraFollower.hpp"
#include "Collision.hpp"
#include "Collider.hpp"
#include "EndState.hpp"
#include "Game.hpp"
#include "GameData.hpp"
#include "InputManager.hpp"
#include "PenguinBody.hpp"
#include "Sound.hpp"
#include "TileMap.hpp"
#include "Vec2.hpp"

StageState::StageState() : music("assets/audio/stageState.ogg") {
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

  // Penguin
  GameObject *penguinObj = new GameObject();
  penguinObj->box.x = 704;
  penguinObj->box.y = 640;

  PenguinBody *pbody = new PenguinBody(*penguinObj);
  penguinObj->AddComponent(pbody);

  objectArray.emplace_back(penguinObj);

  // Alien
  GameObject *alienObj = new GameObject();
  alienObj->box.x = 512;
  alienObj->box.y = 300;

  Alien *alien  = new Alien(*alienObj, 5, GetObjectPtr(penguinObj));
  alienObj->AddComponent(alien);

  GameObject *alienObj2 = new GameObject();
  alienObj2->box.x = 1024;
  alienObj2->box.y = 800;

  Alien *alien2  = new Alien(*alienObj2, 6, GetObjectPtr(penguinObj));
  alienObj2->AddComponent(alien2);

  objectArray.emplace_back(alienObj);
  objectArray.emplace_back(alienObj2);

  if (music.IsOpen())
    music.Play();
}

StageState::~StageState() {
  objectArray.clear();
}

void StageState::LoadAssets() {
  bg->Open("assets/img/ocean.jpg");
  bg->SetClip(0, 0, 1024, 600);
}

void StageState::Start() {
  LoadAssets();
  StartArray();

  started = true;
}

void StageState::Update(float dt) {
  // Input();
	InputManager &input = InputManager::GetInstance();
  Camera &camera      = Camera::GetInstance();

  if (input.KeyPress(ESCAPE_KEY))
    popRequested |= true;

	if (GameData::playerVictory || GameData::playerHp == 0) {
    popRequested |= true;

    EndState *end = new EndState();
    Game::GetInstance().Push(end);
  }
  
  quitRequested = input.QuitRequested();
  
  // Atualiza posição da Camera
  camera.Update(dt);

  // Atualiza array de objetos
  UpdateArray(dt);

  // Verificar colisões
  for (uint i = 0; i < objectArray.size(); i++) {
    Collider *colliderA = (Collider*) objectArray[i]->GetComponent("Collider");

    if (colliderA == nullptr)
      continue;

    for (uint j = i + 1; j < objectArray.size(); j++) {
      Collider *colliderB = (Collider*) objectArray[j]->GetComponent("Collider");

      if (colliderB == nullptr)
        continue;
      
      bool isColliding = Collision::IsColliding(colliderA->box, colliderB->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg);
      
      if (isColliding) {
        objectArray[i]->NotifyCollision(*objectArray[j]);
        objectArray[j]->NotifyCollision(*objectArray[i]);
      }
    }
  }

  for (uint i = 0; i < objectArray.size(); i++) {
    if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin() + i);
    }
  }
}

void StageState::Render() {
  RenderArray();
}
