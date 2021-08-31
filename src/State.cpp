#include "include/Game.hpp"

class State {
  private:
    bool quitRequested;
    Sprite bg;
    // Music music;

  public:
    State() {
      quitRequested = false;
      bg = Sprite();
    }

    void LoadAssets() {
      bg.Open("../assets/img/ocean.jpg");
    }

    void Update() {
      if (SDL_QuitRequested())
        quitRequested = true;
    }

    void Render() {
      bg.Render(0, 0);
    }

    bool QuitRequested() {
      return quitRequested;
    }

    void Run(SDL_Renderer *renderer) {
      while (!quitRequested) {
        Update();
        Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
      }
    }
};