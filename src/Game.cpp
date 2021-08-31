#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/Game.hpp"

class Game {
  private:
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;

    Game (string title, int width, int height) {
      if (instance != nullptr)
        instance = this;
      
      // Inicializacao do SDL
      if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Erro ao inicializar SDL: %s", SDL_GetError());
        return;
      }

      // Inicializacao do SDL IMG
      if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        SDL_Log("Erro ao inicializar SDL IMG!");
        return;
      }

      // Inicializacao do SDL Mixer
      Mix_Init(MIX_INIT_OGG);

      if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        SDL_Log("Erro ao inicializar SDL Mix!");
        return;
      }

      Mix_AllocateChannels(32);

      // Criando a janela
      window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

      // Criando renderizador
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

  public:
    ~Game() {
      Mix_CloseAudio();
      Mix_Quit();
      IMG_Quit();
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
    }

    State& GetState() {
      return *state;
    }

    SDL_Renderer *GetRenderer() {
      return renderer;
    }

    void Run() {
      
    }

    static Game &GetInstance() {
      if (instance != nullptr)
        return;
      
      instance = new Game("O Jogo", 1024, 600);
      return *instance;
    }
};