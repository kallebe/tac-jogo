#ifndef PENGUIN_CANNON_HPP
#define PENGUIN_CANNON_HPP

#include "Component.hpp"
#include "Vec2.hpp"

using namespace std;

class PenguinCannon : public Component {
  private:
    weak_ptr<GameObject> pbody;
    float angle;

  public:
    PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody);

    void Update(float dt);
    void Render();
    bool Is(string type);
    void Shoot();
    void Start() {}
};

#endif
