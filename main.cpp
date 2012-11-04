#include "Game.h"
using namespace std;

int main(int argc, char * argv[])
{
  Game game(argc, argv,"matrix", "slowa","litery");
  game.run();
  return 0;
}
