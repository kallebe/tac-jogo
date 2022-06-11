#ifndef MINION_HPP
#define MINION_HPP

#include "Component.hpp"
#include "Vec2.hpp"

#define PI                3.14159265
#define DESLOCAMENTO_ARCO 5.625
#define RAIO_CIRCULO      150

using namespace std;

class Minion : public Component {
  private:
    weak_ptr<GameObject> alienCenter;
    float                arc;

  public:
    Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

    void Update(float dt);
    void Render() {};
    void Start();
    bool Is(string type);
    void Shoot(Vec2 target);
};

#endif
