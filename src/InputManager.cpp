#include "InputManager.hpp"

void InputManager::Update() {
  SDL_Event event;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);
  quitRequested = false;
  updateCounter++;

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
			  quitRequested = true;
        break;

      case SDL_MOUSEBUTTONDOWN:
			  mouseState[event.button.button - 1]   = true;
        mouseUpdate[event.button.button - 1]  = updateCounter;
        break;

      case SDL_MOUSEBUTTONUP:
			  mouseState[event.button.button - 1]   = false;
        mouseUpdate[event.button.button - 1]  = updateCounter;
        break;

      case SDL_KEYDOWN:
        if (event.key.repeat)
          break;

        if (event.key.keysym.sym == ESCAPE_KEY) {
          quitRequested = true;

        } else {
          int index = event.key.keysym.sym;

          // Ajustes para teclas que não têm valor de caractere
          if (index >= 0x40000000)
            index -= 0x3FFFFF81;
          
          keyState[index]   = true;
          keyUpdate[index]  = updateCounter;
        }

        break;

      case SDL_KEYUP:
        if (event.key.repeat)
          break;

        int index = event.key.keysym.sym;

        // Ajustes para teclas que não têm valor de caractere
        if (index >= 0x40000000)
          index -= 0x3FFFFF81;
        
        keyState[index]   = false;
        keyUpdate[index]  = updateCounter;

        break;
    }
	}
}

InputManager::InputManager() {
  for (int i = 0; i < 6; i++) {
    mouseState[i]  = false;
    mouseUpdate[i] = false;
  }

  for (int i = 0; i < 416; i++) {
    keyState[i]  = false;
    keyUpdate[i] = 0;
  }

  quitRequested = false;
  updateCounter = 0;
  mouseX = 0;
  mouseY = 0;
}

InputManager& InputManager::GetInstance() {
  static InputManager instance;
  return instance;
}

bool InputManager::KeyPress(int key) {
  // Ajustes para teclas que não têm valor de caractere
  if (key >= 0x40000000)
    key -= 0x3FFFFF81;
  
  return keyUpdate[key] == updateCounter && keyState[key];
}

bool InputManager::KeyRelease(int key) {
  // Ajustes para teclas que não têm valor de caractere
  if (key >= 0x40000000)
    key -= 0x3FFFFF81;
  
  return keyUpdate[key] == updateCounter && !keyState[key];
}

bool InputManager::IsKeyDown(int key) {
  // Ajustes para teclas que não têm valor de caractere
  if (key >= 0x40000000)
    key -= 0x3FFFFF81;
  
  return keyState[key];
}

bool InputManager::MousePress(int button) {
  return mouseUpdate[button - 1] == updateCounter && mouseState[button - 1];
}

bool InputManager::MouseRelease(int button) {  
  return mouseUpdate[button - 1] == updateCounter && !mouseState[button - 1];
}

bool InputManager::IsMouseDown(int button) {
  return mouseState[button - 1];
}

int InputManager::GetMouseX() {
  return mouseX;
}

int InputManager::GetMouseY() {
  return mouseY;
}

bool InputManager::QuitRequested() {
  return quitRequested;
}

InputManager::~InputManager() {}
