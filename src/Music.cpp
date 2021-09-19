#include "Music.hpp"
#include "Game.hpp"

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
  music = Mix_LoadMUS(&file[0]);

  if (music == nullptr)
    SDL_Log("Erro ao abrir musica: %s", Mix_GetError());
}

bool Music::IsOpen() {
  return music != nullptr;
}

Music::~Music() {
  Stop();
  Mix_FreeMusic(music);
}
