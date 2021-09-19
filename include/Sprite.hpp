#ifndef SPRITE_HPP
#define SPRITE_HPP

// #include "Game.hpp"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL
#include "SDL_include.h"
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
    Sprite(string file);
    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
};

#endif
