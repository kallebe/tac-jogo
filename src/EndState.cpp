#include "EndState.hpp"

#include "Game.hpp"
#include "GameData.hpp"
#include "InputManager.hpp"
#include "PenguinBody.hpp"
#include "TitleState.hpp"

EndState::EndState() {
  backgroundMusic = GameData::playerVictory ? Music("assets/audio/endStateWin.ogg") : Music("assets/audio/endStateLose.ogg");

  GameObject *bgGo = new GameObject();
  bgGo->box.x = 0;
  bgGo->box.y = 0;

  bg = new Sprite(*bgGo);
  bgGo->AddComponent(bg);

  AddObject(bgGo);

  if (backgroundMusic.IsOpen())
    backgroundMusic.Play();
}

EndState::~EndState() {

}

void EndState::LoadAssets() {
  GameData::playerVictory ? bg->Open("assets/img/win.jpg") : bg->Open("assets/img/lose.jpg");
  bg->SetClip(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void EndState::Update(float dt) {
  InputManager &input = InputManager::GetInstance();

  if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested())
    quitRequested |= true;

  if (input.KeyPress(SPACE_KEY)) {
    popRequested |= true;

    GameData::playerHp = PENGUIN_HP;
    GameData::playerVictory = false;

    TitleState *title = new TitleState();

    Game::GetInstance().Push(title);
  }
}

void EndState::Render() {
  RenderArray();
}

void EndState::Start() {
  LoadAssets();
  StartArray();

  started = true;
}

void EndState::Pause() {}
void EndState::Resume() {}
