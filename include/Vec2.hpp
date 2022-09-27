#ifndef VEC2_HPP
#define VEC2_HPP

#include "Rect.hpp"

class Vec2 {
  public:
    float x, y;

    Vec2();
    Vec2(float x, float y);
    Vec2 Rotate( float rad);
    float Size();

    Vec2 operator+(Vec2 const &vector);
    Vec2 operator-(Vec2 const &vector);
    Vec2 operator+(Rect rect);
    Vec2 operator-(Rect rect);
    Vec2 operator*(const float rhs) const;
};

#endif
