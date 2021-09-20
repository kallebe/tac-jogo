#ifndef RECT_HPP
#define RECT_HPP

class Rect {
  public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);
    
    bool Contains(float x, float y);
};

#endif
