#include "Camera.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "Vec2.hpp"
#include <math.h>

#ifdef DEBUG
  #include "Camera.hpp"
  #include "Game.hpp"

  #include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated) {
  this->scale = scale;
  this->offset = offset;
}

void Collider::Update(float dt) {
  this->box = associated.box;
  this->box.w *= scale.x;
  this->box.h *= scale.y;
  this->box.x  = associated.box.GetMiddleX() - this->box.w/2 + this->offset.x;
  this->box.y  = associated.box.GetMiddleY() - this->box.h/2 + this->offset.y;
}

void Collider::Render() {
  #ifdef DEBUG
    Camera &camera = Camera::GetInstance();
    Vec2 center(box.GetCenter());
    SDL_Point points[5];

    Vec2 point = (Vec2(box.x, box.y) - center).Rotate(associated.angleDeg/(180/M_PI)) + center - camera.pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};
    
    point = (Vec2(box.x + box.w, box.y) - center).Rotate(associated.angleDeg/(180/M_PI)) + center - camera.pos;
    points[1] = {(int)point.x, (int)point.y};
    
    point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate(associated.angleDeg/(180/M_PI)) + center - camera.pos;
    points[2] = {(int)point.x, (int)point.y};
    
    point = (Vec2(box.x, box.y + box.h) - center).Rotate(associated.angleDeg/(180/M_PI)) + center - camera.pos;
    points[3] = {(int)point.x, (int)point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
  #endif // DEBUG
}

bool Collider::Is(string type) {
  return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}
