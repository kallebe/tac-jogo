#include "Game.hpp"
#include "StageState.hpp"

int main(int argc, char** argv) {
  Game &game = Game::GetInstance();

  StageState *state = new StageState();
  game.Push(state);
  game.Run();

  return 0;
}
