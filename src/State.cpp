#include "../include/Game.hpp"

State::State() {
  quitRequested = false;
  bg = Sprite();
  music = Music("assets/audio/stageState.ogg");

  if (music.IsOpen())
    music.Play();
}

void State::LoadAssets() {
  bg.Open("assets/img/ocean.jpg");
  bg.SetClip(0, 0, 1024, 600);
}

void State::Update() {
  if (SDL_QuitRequested())
    quitRequested = true;
}

void State::Render() {
  bg.Render(0, 0);
}

bool State::QuitRequested() {
  return quitRequested;
}

void State::Run() {
  Game &game = Game::GetInstance();

  while (!quitRequested) {
    Update();
    Render();
    SDL_RenderPresent(game.GetRenderer());
    SDL_Delay(33);
  }
}
