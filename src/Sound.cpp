#include "Sound.hpp"

Sound::Sound(GameObject& associated) : Component(associated) {
  chunk = nullptr;
}

Sound::Sound(GameObject& associated, string file) : Sound(associated) {
  Open(file);
}

Sound::~Sound() {
  if (!chunk)
    return;
  
  Stop();
  Mix_FreeChunk(chunk);
}

void Sound::Play(int times) {
  channel = Mix_PlayChannel(-1, chunk, times-1);

  if (channel == -1)
    SDL_Log("Mix_PlayChannel: %s\n", Mix_GetError());
}

void Sound::Stop() {
  if (!chunk)
    return;
  
  Mix_HaltChannel(channel);
}

void Sound::Open(string file) {
  chunk = Mix_LoadWAV(&file[0]);

  if(!chunk)
    SDL_Log("Mix_LoadWAV: %s\n", Mix_GetError());
}

bool Sound::IsOpen() {
  return chunk != nullptr;
}

bool Sound::Is(string type) {
  return type == "Sound";
}
