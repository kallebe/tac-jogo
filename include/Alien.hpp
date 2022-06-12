#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "Component.hpp"
#include "Vec2.hpp"
#include <queue>

using namespace std;

class Alien : public Component {
  private:
    Vec2  speed;
    Vec2  pos;
    int   hp;
    int   nMinions;
    class Action;

    vector<weak_ptr<GameObject>> minionArray;
    queue<Action> taskQueue;
  
  public:
    Alien(GameObject& associated, int numMinions);
    ~Alien();

    void Update(float dt);
    void Render();
    void Start();
    bool Is(string type);
};

class Alien::Action {
  public:
    enum ActionType { MOVE, SHOOT };

    Vec2  pos;
    float angle;
    ActionType type;

    Action(ActionType type, float x, float y);
};

#endif
