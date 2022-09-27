#ifndef RECT_HPP
#define RECT_HPP

class Vec2;
class Rect {
  public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);
    
    float GetMiddleX();
    float GetMiddleY();
    Vec2  GetCenter();
    bool Contains(float x, float y);
};

#endif
