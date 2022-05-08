#ifndef STATE_HPP
#define STATE_HPP

#include "Sprite.hpp"
#include "Music.hpp"
#include <memory>

using namespace std;

class State {
  private:
    bool quitRequested;
    Sprite *bg;
    Music music;
    vector<unique_ptr<GameObject>> objectArray;

  public:
    State();
    ~State();

    void LoadAssets();
    void Update(float dt);
    void Render();
    bool QuitRequested();
    void Run();
    void AddObject(int mouseX, int mouseY);
    // void Input();
};

#endif
