#include "Music.hpp"

Music::Music() {
  music = nullptr;
}

Music::Music(string file) {
  Open(file);
}

void Music::Play(int times) {
  Mix_PlayMusic(music, times);
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
