#ifndef VEC2_HPP
#define VEC2_HPP

class Vec2 {
  public:
    float x, y;

    Vec2();
    Vec2(float x, float y);
    Vec2 GetRotated(float deg);
    float Size();

    Vec2 operator+(Vec2 const &vector);
    Vec2 operator*(float constant);
};

#endif
