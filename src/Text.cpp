#include "Text.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "Resources.hpp"

Text::Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color) : Component(associated) {
  this->fontFile  = fontFile;
  this->fontSize  = fontSize;
  this->style     = style;
  this->text      = text;
  this->color     = color;
  this->texture   = nullptr;

  RemakeTexture();
}

Text::~Text() {
  if (texture != nullptr)
    SDL_DestroyTexture(texture);
}

void Text::Update(float dt) {

}

void Text::Render() {
  Game &game = Game::GetInstance();
  Camera &camera = Camera::GetInstance();

  int width  = static_cast<int>(associated.box.w);
  int height = static_cast<int>(associated.box.h);

  SDL_Rect clipRect = { 0, 0, width, height };
  SDL_Rect destClip = { static_cast<int>(associated.box.x - camera.pos.x), static_cast<int>(associated.box.y - camera.pos.y), width, height };

  SDL_RenderCopyEx(game.GetRenderer(), texture, &clipRect, &destClip, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Text::RemakeTexture() {
  if (texture != nullptr)
    SDL_DestroyTexture(texture);
  
  Game &game = Game::GetInstance();
  Resources &res = Resources::GetInstance();

  font = res.GetFont(fontFile, fontSize);

  if (font == nullptr)
    return;
  
  switch (style) {
  case TextStyle::SOLID:
    {
      SDL_Surface *surface = TTF_RenderText_Solid(font, &text[0], color);
      texture = SDL_CreateTextureFromSurface(game.GetRenderer(), surface);
      SDL_FreeSurface(surface);
    }

    break;
  
  case TextStyle::SHADED:
    {
      SDL_Surface *surface = TTF_RenderText_Shaded(font, &text[0], color, { 0, 0, 0, 255 });
      texture = SDL_CreateTextureFromSurface(game.GetRenderer(), surface);
      SDL_FreeSurface(surface);
    }

    break;
  
  case TextStyle::BLENDED:
    {
      SDL_Surface *surface = TTF_RenderText_Blended(font, &text[0], color);
      texture = SDL_CreateTextureFromSurface(game.GetRenderer(), surface);
      SDL_FreeSurface(surface);
    }

    break;
  
  default:
    break;
  }

  if (texture != nullptr) {
    int width, height;
    
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    associated.box.w = width;
    associated.box.h = height;
  }
}

bool Text::Is(string type) {
  return type == "Text";
}

void Text::SetText(string text) {
  this->text = text;
  RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
  this->style = style;
  RemakeTexture();
}

void Text::SetFontFile(string fontFile) {
  this->fontFile = fontFile;
  RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
  this->fontSize = fontSize;
  RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
  this->color = color;
  RemakeTexture();
}

