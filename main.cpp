#include "Game.h"
using namespace std;

int main(int argc, char * argv[])
{
  Game game(argc, argv,"matrix","lit","slowa");
  game.run();
  return 0;
}
