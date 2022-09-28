#ifndef SOUND_HPP
#define SOUND_HPP

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL
#include "SDL_include.h"
#include "GameObject.hpp"
#include "Component.hpp"

class Sound : public Component {
  private:
    Mix_Chunk *chunk;
    int channel;
  
  public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, string file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(string file);
    bool IsOpen();
    int GetChannel();

    void Update(float dt) {};
    void Render() {};
    void Start() {};
    bool Is(string type);
};

#endif
