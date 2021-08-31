#ifndef STATE_HPP
#define STATE_HPP

#include "Sprite.hpp"

class State {
  private:
    bool quitRequested = false;
    Sprite bg;
    // Music music;
  public:
    State();
    void Update();
    void Render();
    bool QuitRequested();
    void Run();
};

#endif
