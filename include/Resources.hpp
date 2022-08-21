#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>
#include <unordered_map>

using namespace std;

class Resources {
  private:
    static Resources *instance;
    unordered_map<string, SDL_Texture*> imageTable;
    unordered_map<string, Mix_Music*>   musicTable;
    unordered_map<string, Mix_Chunk*>   soundTable;

    Resources();
  
  public:
    SDL_Texture* GetImage(string file);
    void ClearImages();

    Mix_Music* GetMusic(string file);
    void ClearMusics();

    Mix_Chunk* GetSound(string file);
    void ClearSounds();

    static Resources &GetInstance();
};

#endif
