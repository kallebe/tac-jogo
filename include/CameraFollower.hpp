#ifndef CAMERA_FOLLOWER_HPP
#define CAMERA_FOLLWER_HPP

#include "Component.hpp"

using namespace std;

class CameraFollower : public Component {
  public:
    CameraFollower(GameObject& associated);

    void Update(float dt);
    void Render() {}
    bool Is(string type);
};

#endif
