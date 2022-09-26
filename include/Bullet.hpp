#ifndef BULLET_HPP
#define BULLET_HPP

#include "Component.hpp"
#include "Vec2.hpp"

#define BULLET_SPEED        0.00004
#define BULLET_DAMAGE       5
#define BULLET_MAX_DISTANCE 1500

using namespace std;

class Bullet : public Component {
  private:
    Vec2  speed;
    float distanceLeft;
    int   damage;
  
  public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime);

    void Update(float dt);
    void Render() {};
    void Start() {};
    bool Is(string type);
    int  GetDamage();
    void NotifyCollision(GameObject &other);
};

#endif
