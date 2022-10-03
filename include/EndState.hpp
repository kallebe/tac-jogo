#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "Music.hpp"
#include "Sprite.hpp"
#include "State.hpp"

using namespace std;

class EndState : public State {
  private:
    Sprite *bg;
    Music backgroundMusic;
  
  public:
    EndState();
    ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();
    
    void Start();
    void Pause();
    void Resume();
};

#endif
