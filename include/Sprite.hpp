#ifndef SPRITE_HPP
#define SPRITE_HPP

// #include "Game.hpp"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Vec2.hpp"
#include "Component.hpp"
#include <string>

using namespace std;

class Sprite : public Component {
  private:
    SDL_Texture *texture;
    int width;
    int height;
    Vec2 scale;
    SDL_Rect clipRect;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
  
  public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, string file, int frameCount = 1, float frameTime = 1);
    
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    void Render(float x, float y);  
    int  GetWidth();
    int  GetHeight();
    bool IsOpen();
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();
    
    void Update(float dt);
    void Start() {}

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);

    bool Is(string type);
};

#endif
