#include "Camera.hpp"
#include "Game.hpp"
#include "InputManager.hpp"

void Camera::Follow(GameObject *newFocus) {
  focus = newFocus;
}

void Camera::Unfollow() {
  focus = nullptr;
}

void Camera::Update(float dt) {
  if (focus == nullptr) {
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
  } else {
    // Com foco
    pos.x += -focus->box.x + SCREEN_WIDTH/2;
    pos.y += -focus->box.y + SCREEN_HEIGHT/2;
  }
}

Camera::Camera() {
  speed.x = 1.0;
  speed.y = 1.0;
}

Camera& Camera::GetInstance() {
  static Camera instance;
  return instance;
}
