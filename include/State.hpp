#ifndef STATE_HPP
#define STATE_HPP

#include "Sprite.hpp"
#include "Music.hpp"
#include <memory>

using namespace std;

class State {
  private:
    bool    quitRequested;
    bool    started;
    Sprite *bg;
    Music   music;
    vector<shared_ptr<GameObject>> objectArray;

  public:
    State();
    ~State();

    void LoadAssets();
    void Update(float dt);
    void Render();
    bool QuitRequested();
    void Run();
    // void AddObject(int mouseX, int mouseY);
    void Start();
    weak_ptr<GameObject> AddObject(GameObject *go);
    weak_ptr<GameObject> GetObjectPtr(GameObject *go);
};

#endif
