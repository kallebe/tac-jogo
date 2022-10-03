#include "Game.hpp"

#include "InputManager.hpp"
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

  // Inicializacao do SDL TTF
  if (TTF_Init() != 0) {
    SDL_Log("Erro ao inicializar SDL TTF: %s", TTF_GetError());
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
  storedState = nullptr;

  // Inicializando variaveis de temporização
  frameStart = 0;
  dt = SDL_GetTicks() / 1000.0;
}

Game::~Game() {
  // Remove storedState
  if (storedState != nullptr)
    storedState = nullptr;
  
  // Esvazia pilha de States
  while (!stateStack.empty())
    stateStack.pop();

  // Limpa Resourses
  Resources &res = Resources::GetInstance();

  res.ClearImages();
  res.ClearMusics();
  res.ClearSounds();
  res.ClearFonts();

  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

State& Game::GetCurrentState() {
  return *stateStack.top();
}

void Game::Push(State *state) {
  storedState = state;
}

SDL_Renderer* Game::GetRenderer() {
  return renderer;
}

void Game::Run() {
  stateStack.push(unique_ptr<State>(storedState));
  storedState = nullptr;

  if (stateStack.top() == nullptr)
    return;
  
  GetCurrentState().Start();

  while (!stateStack.empty() && !GetCurrentState().QuitRequested()) {
    if (GetCurrentState().PopRequested()) {
      stateStack.pop();

      if (!stateStack.empty())
        GetCurrentState().Resume();
    }

    if (storedState != nullptr) {
      GetCurrentState().Pause();
      stateStack.push(unique_ptr<State>(storedState));

      GetCurrentState().Start();
      storedState = nullptr;
    }

    if (stateStack.empty())
      break;

    InputManager &input = InputManager::GetInstance();
    input.Update();

    GetCurrentState().Update(dt);
    GetCurrentState().Render();
    SDL_RenderPresent(GetRenderer());
    SDL_Delay(33);
  }

  // Limpa Resourses
  Resources &res = Resources::GetInstance();

  res.ClearImages();
  res.ClearMusics();
  res.ClearSounds();
  res.ClearFonts();
}

Game& Game::GetInstance() {
  if (instance != nullptr)
    return *instance;
  
  instance = new Game("Kallebe - 180053485", SCREEN_WIDTH, SCREEN_HEIGHT);
  return *instance;
}

void Game::CalulaDeltaTime() {
  int currentTime = SDL_GetTicks() / 1000.0;

  dt = currentTime - frameStart;
  frameStart = currentTime;
}

float Game::GetDeltaTime() {
  return dt;
}
