#include "TitleState.hpp"

#include "Game.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Sprite.hpp"
#include "StageState.hpp"
#include "Text.hpp"

TitleState::TitleState() {
  GameObject *titleGo = new GameObject();
  titleGo->box.x = 0;
  titleGo->box.y = 0;

  bg = new Sprite(*titleGo);
  titleGo->AddComponent(bg);

  AddObject(titleGo);

  GameObject *textGo = new GameObject();
  textGo->box.x = SCREEN_WIDTH/2;
  textGo->box.y = 0.85 * SCREEN_HEIGHT;

  // Texto para mudança de tela
  text = new Text(*textGo, "assets/font/Call me maybe.ttf", 32, Text::BLENDED, "Pressione Espaco para continuar", { 186, 37, 7, 255 });
  textGo->box.x -= textGo->box.w/2;
  textGo->box.y -= textGo->box.h/2;
  textGo->AddComponent(text);

  AddObject(textGo);

  textTimer    = Timer();
  showText     = false;
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

  textTimer.Update(dt);
  if (textTimer.Get() >= TEXT_BLINK_TIME) {
    showText ? text->SetText("Pressione Espaco para continuar") : text->SetText("");

    textTimer.Restart();
    showText = !showText;
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
