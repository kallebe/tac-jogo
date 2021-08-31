#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "Game.hpp"
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
