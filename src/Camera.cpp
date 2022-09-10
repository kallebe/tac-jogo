#include "Camera.hpp"
#include "InputManager.hpp"

void Camera::Follow(GameObject *newFocus) {
  focus = newFocus;
}

void Camera::Unfollow() {
  focus = nullptr;
}

void Camera::Update(float dt) {
  // Sem foco
  InputManager &input = InputManager::GetInstance();

  if (input.IsKeyDown(LEFT_ARROW_KEY))
    pos.x += speed.x * dt;

  else if (input.IsKeyDown(RIGHT_ARROW_KEY))
    pos.x -= speed.x * dt;

  else if (input.IsKeyDown(UP_ARROW_KEY))
    pos.y += speed.y * dt;

  else if (input.IsKeyDown(DOWN_ARROW_KEY))
    pos.y -= speed.y * dt;
}

Camera::Camera() {
  speed.x = 0.0001;
  speed.y = 0.0001;
}

Camera& Camera::GetInstance() {
  static Camera instance;
  return instance;
}
