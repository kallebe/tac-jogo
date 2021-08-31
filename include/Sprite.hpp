#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Game.hpp"
#include <string>

using namespace std;

class Sprite {
  private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
  
  public:
    Sprite();
    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
};

#endif
