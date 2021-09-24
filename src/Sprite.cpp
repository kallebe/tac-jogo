#include "../include/Sprite.hpp"
#include "Game.hpp"

Sprite::Sprite(GameObject& associated) : Component(associated) {
  texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file) : Sprite(associated) {
  Open(file);
}

Sprite::~Sprite() {
  if (texture != nullptr)
    SDL_DestroyTexture(texture);
}

void Sprite::Open(string file) {
  Game &game = Game::GetInstance();

  if (texture != nullptr)
    SDL_DestroyTexture(texture);
  
  texture = IMG_LoadTexture(game.GetRenderer(), &file[0]);

  if (texture == nullptr) {
    SDL_Log("Erro ao carregar arquivo: %s", SDL_GetError());
    return;
  }

  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  associated.box.w = width; 
  associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render() {
  Game &game = Game::GetInstance();

  SDL_Rect destClip;
  destClip.x = associated.box.x;
  destClip.y = associated.box.y;
  destClip.w = clipRect.w;
  destClip.h = clipRect.h;

  SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &destClip);
}

int Sprite::GetWidth() {
  return width;
}

int Sprite::GetHeight() {
  return height;
}

bool Sprite::IsOpen() {
  return texture != nullptr;
}

bool Sprite::Is(string type) {
  return type == "Sprite";
}
