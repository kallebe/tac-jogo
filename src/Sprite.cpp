#include "include/Sprite.hpp"

class Sprite {
  private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
  
  public:
    Sprite() {
      texture = nullptr;
    }

    Sprite(string file) {
      texture = nullptr;
      Open(file);
    }

    ~Sprite() {
      if (texture != nullptr)
        SDL_DestroyTexture(texture);
    }

    void Open(string file) {
      Game &game = Game::GetInstance();
  
      if (texture != nullptr)
        SDL_DestroyTexture(texture);
      
      texture = IMG_LoadTexture(game.GetRenderer(), &file[0]);

      if (texture == nullptr) {
        SDL_Log("Erro ao carregar arquivo: %s", SDL_GetError());
        return;
      }

      SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
    void SetClip(int x, int y, int w, int h) {
      clipRect.x = x;
      clipRect.y = y;
      clipRect.w = w;
      clipRect.h = h;
    }

    void Render(int x, int y) {
      Game &game = Game::GetInstance();

      SDL_Rect destClip;
      destClip.x = x;
      destClip.y = y;
      destClip.w = clipRect.w;
      destClip.h = clipRect.h;
    
      SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &destClip);
    }

    int GetWidth() {
      return width;
    }

    int GetHeight() {
      return height;
    }

    bool IsOpen() {
      return texture != nullptr;
    }
};
