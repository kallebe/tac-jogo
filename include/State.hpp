#ifndef STATE_HPP
#define STATE_HPP

#include "Sprite.hpp"

class State {
  private:
    bool quitRequested;
    Sprite bg;
    // Music music;
  public:
    State();
    void LoadAssets();
    void Update();
    void Render();
    bool QuitRequested();
    void Run();
};

#endif
