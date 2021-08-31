#ifndef GAME_HPP
#define GAME_HPP

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.hpp"
#include <string>

using namespace std;

class Game {
  private:
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;

    Game(string title, int width, int height);
  public:
    ~Game();
    State& GetState();
    SDL_Renderer *GetRenderer();
    void Run();
    static Game &GetInstance();
};

#endif
