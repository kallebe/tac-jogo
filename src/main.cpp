#include "Game.hpp"
#include "TitleState.hpp"

int main(int argc, char** argv) {
  Game &game = Game::GetInstance();

  TitleState *state = new TitleState();
  game.Push(state);
  game.Run();

  return 0;
}
