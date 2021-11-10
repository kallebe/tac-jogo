#include "../include/Game.hpp"
#include "Resources.hpp"
#include <time.h>

Game* Game::instance;

Game::Game(string title, int width, int height) {
  if (instance == nullptr)
    instance = this;
  
  // Seed randomico
  srand(time(NULL));
  
  // Inicializacao do SDL
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    SDL_Log("Erro ao inicializar SDL: %s", SDL_GetError());
    exit(1);
  }

  // Inicializacao do SDL IMG
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
    SDL_Log("Erro ao inicializar SDL IMG!");
    exit(1);
  }

  // Inicializacao do SDL Mixer
  if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) != (MIX_INIT_OGG | MIX_INIT_MP3)) {
    SDL_Log("Erro ao inicializar SDL Mix: %s", Mix_GetError());
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
    SDL_Log("Erro ao inicializar SDL Mix!");
    exit(1);
  }

  Mix_AllocateChannels(32);

  // Criando a janela
  window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  // Criando renderizador
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Inicializando state
  state = new State();
}

Game::~Game() {
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

State& Game::GetState() {
  return *state;
}

SDL_Renderer* Game::GetRenderer() {
  return renderer;
}

void Game::Run() {
  state->LoadAssets();
  state->Run();

  Resources &res = Resources::GetInstance();

  res.ClearImages();
  res.ClearMusics();
  res.ClearSounds();
}

Game& Game::GetInstance() {
  if (instance != nullptr)
    return *instance;
  
  instance = new Game("Kallebe - 180053485", 1024, 600);
  return *instance;
}