#include "TitleState.hpp"

#include "Game.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Sprite.hpp"
#include "StageState.hpp"

TitleState::TitleState() {
  GameObject *titleGo = new GameObject();
  titleGo->box.x = 0;
  titleGo->box.y = 0;

  bg = new Sprite(*titleGo);
  titleGo->AddComponent(bg);

  objectArray.emplace_back(titleGo);
}

void TitleState::Update(float dt) {
  InputManager &input = InputManager::GetInstance();

  if (input.KeyPress(ESCAPE_KEY))
    popRequested |= true;
  
  quitRequested = input.QuitRequested();

  if (input.KeyPress(SPACE_KEY)) {
    StageState *stage = new StageState();

    Game::GetInstance().Push(stage);
  }
}

void TitleState::LoadAssets() {
  bg->Open("assets/img/title.jpg");
  bg->SetClip(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void TitleState::Start() {
  LoadAssets();
  StartArray();

  started = true;
}

void TitleState::Render() {
  RenderArray();
}

void TitleState::Resume() {}
void TitleState::Pause() {}

TitleState::~TitleState() {
  objectArray.clear();
}
