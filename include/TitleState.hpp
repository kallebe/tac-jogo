#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include "Sprite.hpp"
#include "State.hpp"

using namespace std;

class TitleState : public State {
  private:
    Sprite *bg;

  public:
    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(float dt);
    void Render();
    
    void Start();
    void Resume();
    void Pause();
};

#endif
