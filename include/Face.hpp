#ifndef FACE_HPP
#define FACE_HPP

#include "GameObject.hpp"
#include "Component.hpp"
#include "Vec2.hpp"

class Face : public Component {
  private:
    int hitpoints;
    Vec2 pos;
  
  public:
    Face(GameObject& associated);

    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif
