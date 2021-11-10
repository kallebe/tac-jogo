#include "Music.hpp"
#include "Game.hpp"
#include "Resources.hpp"

Music::Music() {
  music = nullptr;
}

Music::Music(string file) {
  Open(file);
}

void Music::Play(int times) {
  if (Mix_PlayMusic(music, times) == -1)
    SDL_Log("Erro ao tocar musica: %s", Mix_GetError());
}

void Music::Stop(int msToStop) {
  Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
  Resources &res = Resources::GetInstance();
  music = res.GetMusic(file);
}

bool Music::IsOpen() {
  return music != nullptr;
}

Music::~Music() {
  Stop();
}
