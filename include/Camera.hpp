#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.hpp"
#include "Vec2.hpp"

using namespace std;

class Camera {
  private:
    GameObject *focus;

    Camera();

  public:
    Vec2 pos;
    Vec2 speed;

    void Follow(GameObject *newFocus);
    void Unfollow();
    void Update(float dt);

    static Camera& GetInstance();
};

#endif
