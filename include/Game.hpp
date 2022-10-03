#ifndef GAME_HPP
#define GAME_HPP

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.hpp"
#include <stack>
#include <string>

#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 600

using namespace std;

class Game {
  private:
    static Game   *instance;
    SDL_Window    *window;
    SDL_Renderer  *renderer;
    State         *storedState;
    stack<unique_ptr<State>> stateStack;

    int   frameStart;
    float dt;

    void CalulaDeltaTime();

  public:
    Game(string title, int width, int height);
    ~Game();

    static Game &GetInstance();
    SDL_Renderer *GetRenderer();
    State &GetCurrentState();

    void Push(State *state);
    void Run();
    float GetDeltaTime();
};

#endif
