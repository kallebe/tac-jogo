#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#define INCLUDE_SDL
#include "SDL_include.h"

#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define SPACE_KEY         SDLK_SPACE
#define FOWARD_W_KEY      SDLK_w
#define BACKWARD_S_KEY    SDLK_s
#define COUNTERCLOCKWISE_A_KEY  SDLK_a
#define CLOCKWISE_D_KEY         SDLK_d
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT

using namespace std;

class InputManager {
  private:
    bool mouseState[6];
    int  mouseUpdate[6];
    bool keyState[416];
    int  keyUpdate[416];
    bool quitRequested;
    int  updateCounter;
    int  mouseX, mouseY;

    InputManager();
    ~InputManager();

  public:
    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager& GetInstance();
};

#endif
