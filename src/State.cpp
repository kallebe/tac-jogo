#include "../include/Game.hpp"
#include "Face.hpp"
#include "Sound.hpp"
#include "TileMap.hpp"
#include "Vec2.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"

State::State() : music("assets/audio/stageState.ogg") {
  quitRequested = false;

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

	objectArray.emplace_back(tm);

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

void State::Update(float dt) {
  // Input();
	InputManager &input = InputManager::GetInstance();
  Camera &camera      = Camera::GetInstance();

	quitRequested = input.KeyPress(ESCAPE_KEY) || input.QuitRequested();

  // Adiciona Face
	if (input.KeyPress(SPACE_KEY))
		AddObject(input.GetMouseX(), input.GetMouseY());
  
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

void State::AddObject(int mouseX, int mouseY) {
  GameObject *go      = new GameObject();
  Camera     &camera  = Camera::GetInstance();

  Sprite *enemy = new Sprite(*go, "assets/img/penguinface.png");
  go->AddComponent(enemy);

  go->box.x = mouseX - camera.pos.x + enemy->GetWidth()/2;
  go->box.y = mouseY - camera.pos.y + enemy->GetHeight()/2;

  Sound *sound = new Sound(*go, "assets/audio/boom.wav");
  go->AddComponent(sound);

  Face *face = new Face(*go);
  go->AddComponent(face);

  objectArray.emplace_back(go);
}

// void State::Input() {
//   SDL_Event event;
// 	int mouseX, mouseY;

// 	// Obtenha as coordenadas do mouse
// 	SDL_GetMouseState(&mouseX, &mouseY);

// 	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
// 	while (SDL_PollEvent(&event)) {

// 		// Se o evento for quit, setar a flag para terminação
// 		if(event.type == SDL_QUIT) {
// 			quitRequested = true;
// 		}
		
// 		// Se o evento for clique...
// 		if(event.type == SDL_MOUSEBUTTONDOWN) {
// 			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
// 			for(int i = objectArray.size() - 1; i >= 0; --i) {
// 				// Obtem o ponteiro e casta pra Face.
// 				GameObject* go = (GameObject*) objectArray[i].get();
// 				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
// 				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
// 				// ao usar get(), violamos esse princípio e estamos menos seguros.
// 				// Esse código, assim como a classe Face, é provisório. Futuramente, para
// 				// chamar funções de GameObjects, use objectArray[i]->função() direto.

// 				if (go->box.Contains((float) mouseX, (float) mouseY)) {
// 					Face* face = (Face*) go->GetComponent("Face");

// 					if (face != nullptr) {
// 						// Aplica dano
// 						face->Damage(std::rand() % 10 + 10);
// 						// Sai do loop (só queremos acertar um)
// 						break;
// 					}
// 				}
// 			}
// 		}

// 		if (event.type == SDL_KEYDOWN) {
// 			// Se a tecla for ESC, setar a flag de quit
// 			if (event.key.keysym.sym == SDLK_ESCAPE) {
// 				quitRequested = true;
// 			}
// 			// Se não, crie um objeto
// 			else {
// 				Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
// 				AddObject((int) objPos.x, (int) objPos.y);
// 			}
// 		}
// 	}
// }
