#ifndef MUSIC_HPP
#define MUSIC_HPP

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>

using namespace std;

class Music {
  private:
    Mix_Music *music;
  
  public:
    Music();
    Music(string file);
    ~Music();
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool IsOpen();
};

#endif
