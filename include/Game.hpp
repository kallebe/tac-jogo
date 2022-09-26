#ifndef GAME_HPP
#define GAME_HPP

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.hpp"
#include <iostream>
#include <string>

#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 600

using namespace std;

class Game {
  private:
    static Game   *instance;
    SDL_Window    *window;
    SDL_Renderer  *renderer;
    State         *state;

    int   frameStart;
    float dt;

    Game(string title, int width, int height);
    void CalulaDeltaTime();

  public:
    ~Game();
    State&        GetState();
    SDL_Renderer *GetRenderer();
    void          Run();
    static Game  &GetInstance();
    float         GetDeltaTime();
};

#endif
