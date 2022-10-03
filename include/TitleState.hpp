#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include "Sprite.hpp"
#include "State.hpp"
#include "Text.hpp"
#include "Timer.hpp"

#define TEXT_BLINK_TIME 4.0

using namespace std;

class TitleState : public State {
  private:
    Sprite *bg;
    Text *text;
    bool showText;
    Timer textTimer;

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
