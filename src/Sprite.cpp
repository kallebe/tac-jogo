#include "../include/Sprite.hpp"
#include "Game.hpp"
#include "Resources.hpp"

Sprite::Sprite(GameObject& associated) : Component(associated) {
  texture = nullptr;
  scale.x = 1;
  scale.y = 1;

  this->frameCount = 1;
  this->frameTime  = 1;
  this->currentFrame  = 0;
  this->timeElapsed   = 0;
  this->selfDestructCounter = Timer();
}

Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Sprite(associated) {
  scale.x = 1;
  scale.y = 1;

  this->frameCount    = frameCount;
  this->frameTime     = frameTime;
  this->currentFrame  = 0;
  this->timeElapsed   = 0;
  this->secondsToSelfDestruct = secondsToSelfDestruct;
  this->selfDestructCounter   = Timer();

  Open(file);
}

void Sprite::Open(string file) {
  Resources &res = Resources::GetInstance();
  texture = res.GetImage(file);

  if (texture == nullptr) {
    SDL_Log("Erro ao carregar arquivo: %s", SDL_GetError());
    return;
  }

  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  SetClip(0, 0, width/frameCount, height);
  associated.box.w = width;
  associated.box.h = height;
}

void Sprite::Update(float dt) {
  if (frameCount == 1)
    return;
  
  if (secondsToSelfDestruct > 0) {
    selfDestructCounter.Update(dt/100000);
  
    if (selfDestructCounter.Get() >= secondsToSelfDestruct)
      associated.RequestDelete();
  }
  
  timeElapsed += dt;

  // Avança o frame e seta o clipe
  if (timeElapsed > frameTime) {
    timeElapsed = 0;
    currentFrame++;

    if (currentFrame >= frameCount)
      currentFrame = 0;

    int frameWidth = width / frameCount;
    SetClip(frameWidth * currentFrame, 0, frameWidth, height);
  }
}

void Sprite::SetFrame(int frame) {
  this->currentFrame = frame;

  int frameWidth = width / frameCount;
  SetClip(frameWidth * currentFrame, 0, frameWidth, height);
}

void Sprite::SetFrameCount(int frameCount) {
  this->frameCount = frameCount;
  // TODO: resetar frameInicial e recalcular box do GameObject
}

void Sprite::SetFrameTime(float frameTime) {
  this->frameTime = frameTime;
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render() {
  Render(associated.box.x, associated.box.y);
}

void Sprite::Render(float x, float y) {
  Game &game = Game::GetInstance();

  SDL_Rect destClip;
  destClip.x = x;
  destClip.y = y;
  destClip.w = clipRect.w * this->scale.x;
  destClip.h = clipRect.h * this->scale.y;

  SDL_RenderCopyEx(game.GetRenderer(), texture, &clipRect, &destClip, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

int Sprite::GetWidth() {
  return width * scale.x / frameCount;
}

int Sprite::GetHeight() {
  return height * scale.y;
}

Vec2 Sprite::GetScale() {
  return this->scale;
}

void Sprite::SetScale(float scaleX, float scaleY) {
  this->scale.x = scaleX;
  this->scale.y = scaleY;
}

bool Sprite::IsOpen() {
  return texture != nullptr;
}

bool Sprite::Is(string type) {
  return type == "Sprite";
}
