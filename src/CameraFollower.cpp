#include "CameraFollower.hpp"
#include "Camera.hpp"

CameraFollower::CameraFollower(GameObject& associated) : Component(associated) {}

void CameraFollower::Update(float dt) {
  Camera &camera = Camera::GetInstance();

  associated.box.x = camera.pos.x;
  associated.box.y = camera.pos.y;
}

bool CameraFollower::Is(string type) {
  return type == "CameraFollower";
}
