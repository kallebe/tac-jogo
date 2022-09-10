#ifndef PENGUIN_BODY_HPP
#define PENGUIN_BODY_HPP

#include "Component.hpp"
#include "Vec2.hpp"

#define PENGUIN_ACCELERATION  0.00001
#define MAX_PENGUIN_SPEED     0.0004
#define PENGUIN_ANGULAR_SPEED 0.00004  

using namespace std;

class PenguinBody : public Component {
  private:
    weak_ptr<GameObject> pcannon;
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
};

#endif
