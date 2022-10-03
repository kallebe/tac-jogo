#ifndef PENGUIN_BODY_HPP
#define PENGUIN_BODY_HPP

#include "Component.hpp"
#include "Vec2.hpp"

#define PENGUIN_ACCELERATION  10.0
#define MAX_PENGUIN_SPEED     100.0
#define PENGUIN_ANGULAR_SPEED 40.0

#define PENGUIN_HP 100

using namespace std;

class PenguinBody : public Component {
  private:
    weak_ptr<GameObject> pcannon;
    weak_ptr<GameObject> textHp;
    Vec2    speed;
    Vec2    pos;
    float   linearSpeed;
    float   angle;
    int     hp;
  
  public:
    PenguinBody *player;

    PenguinBody(GameObject &associated);
    ~PenguinBody();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject &other);
    Vec2 GetPos();
};

#endif
