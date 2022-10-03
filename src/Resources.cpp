#include "Resources.hpp"
#include "Game.hpp"

Resources *Resources::instance;

SDL_Texture* Resources::GetImage(string file) {
  Game &game = Game::GetInstance();

  auto texture = imageTable.find(file);
  if (texture != imageTable.end())
    return texture->second;
  
  SDL_Texture *newTexture = IMG_LoadTexture(game.GetRenderer(), &file[0]);
  if (newTexture == nullptr) {
    SDL_Log("Erro ao carregar textura: %s", SDL_GetError());
    return nullptr;
  }

  imageTable.insert({ file, newTexture });
  return newTexture;
}

Mix_Music* Resources::GetMusic(string file) {
  auto music = musicTable.find(file);
  if (music != musicTable.end())
    return music->second;
  
  Mix_Music *newMusic = Mix_LoadMUS(&file[0]); 
  if (newMusic == nullptr) {
    SDL_Log("Erro ao carregar musica: %s", SDL_GetError());
    return nullptr;
  }

  musicTable.insert({ file, newMusic });
  return newMusic;
}

Mix_Chunk* Resources::GetSound(string file) {
  auto sound = soundTable.find(file);
  if (sound != soundTable.end())
    return sound->second;
  
  Mix_Chunk *newSound = Mix_LoadWAV(&file[0]); 
  if (newSound == nullptr) {
    SDL_Log("Erro ao carregar audio: %s", SDL_GetError());
    return nullptr;
  }

  soundTable.insert({ file, newSound });
  return newSound;
}

TTF_Font* Resources::GetFont(string file, int ptSize) {
  auto font = fontTable.find(file + to_string(ptSize));
  if (font != fontTable.end())
    return font->second;
  
  TTF_Font *newFont = TTF_OpenFont(&file[0], ptSize); 
  if (newFont == nullptr) {
    SDL_Log("Erro ao carregar fonte: %s", SDL_GetError());
    return nullptr;
  }

  fontTable.insert({ file + to_string(ptSize), newFont });
  return newFont;
}

void Resources::ClearImages() {
  for (const pair<string, SDL_Texture*>& pairTexture : imageTable) {
    SDL_DestroyTexture(pairTexture.second);
  }
  imageTable.clear();
}

void Resources::ClearMusics() {
  for (const pair<string, Mix_Music*>& pairMusic : musicTable) {
    Mix_FreeMusic(pairMusic.second);
  }
  musicTable.clear();
}

void Resources::ClearSounds() {
  for (const pair<string, Mix_Chunk*>& pairSound : soundTable) {
    Mix_FreeChunk(pairSound.second);
  }
  soundTable.clear();
}

void Resources::ClearFonts() {
  for (const pair<string, TTF_Font*>& pairFont : fontTable) {
    TTF_CloseFont(pairFont.second);
  }
  fontTable.clear();
}

Resources::Resources() {
  if (instance == nullptr)
    instance = this;
}

Resources& Resources::GetInstance() {
  if (instance != nullptr)
    return *instance;
  
  instance = new Resources();
  return *instance;
}
