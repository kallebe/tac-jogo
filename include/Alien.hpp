#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "Component.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"
#include <queue>

#define ALIEN_HP 40
#define ALIEN_MAX_RESTING_TIME 10

using namespace std;

class Alien : public Component {
  private:
    Vec2  speed;
    Vec2  pos;
    int   hp;
    int   nMinions;
    weak_ptr<GameObject> pbody;

    enum  AlienState { MOVING, RESTING };
    AlienState  state;
    Timer       restTimer;
    int         restTime;
    Vec2        destination;

    vector<weak_ptr<GameObject>> minionArray;
  
  public:
    static int alienCount;

    Alien(GameObject& associated, int numMinions, weak_ptr<GameObject> pbody);
    ~Alien();

    void Update(float dt);
    void Render();
    void Start();
    bool Is(string type);
    void NotifyCollision(GameObject &other);
    void RemoveMinion(weak_ptr<GameObject> minion);
};

#endif
