#ifndef STAGE_STATE_HPP
#define STAGE_STATE_HPP

#include "State.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include <memory>

using namespace std;

class StageState : public State {
  private:
    Sprite *bg;
    Music   music;

  public:
    StageState();
    ~StageState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause() {};
    void Resume() {};
};

#endif
