#ifndef PENGUIN_CANNON_HPP
#define PENGUIN_CANNON_HPP

#include "Component.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"

// Cooldown em segundos para proximo tiro
#define COOLDOWN_TIME 5.0

using namespace std;

class PenguinCannon : public Component {
  private:
    weak_ptr<GameObject> pbody;
    float angle;
    Timer cooldown;

  public:
    PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody);

    void Update(float dt);
    void Render();
    bool Is(string type);
    void Shoot();
    void Start() {}
    void NotifyCollision(GameObject &other);
};

#endif
