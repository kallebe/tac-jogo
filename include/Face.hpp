#ifndef FACE_HPP
#define FACE_HPP

#include "GameObject.hpp"
#include "Component.hpp"

class Face : public Component {
  private:
    int hitpoints;
  
  public:
    Face(GameObject& associated);

    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif
