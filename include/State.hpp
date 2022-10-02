#ifndef STATE_HPP
#define STATE_HPP

#include "GameObject.hpp"
#include <memory>

using namespace std;

class State {
  protected:
    bool    quitRequested;
    bool    popRequested;
    bool    started;
    vector<shared_ptr<GameObject>> objectArray;

    void StartArray();
    void virtual UpdateArray(float dt);
    void virtual RenderArray();

  public:
    State();
    virtual ~State();

    void virtual LoadAssets() = 0;
    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    
    void virtual Start() = 0;
    void virtual Pause() = 0;
    void virtual Resume() = 0;

    weak_ptr<GameObject> virtual AddObject(GameObject *go);
    weak_ptr<GameObject> virtual GetObjectPtr(GameObject *go);

    bool QuitRequested();
    bool PopRequested();
};

#endif
