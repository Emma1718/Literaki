#include "Game.h"

int main(int argc, char * argv[])
{
  Game game(argc, argv,"matrix");
  game.run();
  // Dictionary dict;
  // dict.load("plik.txt");
  // dict.checkWord("ktury"); //false
  // dict.checkWord("ser") //true
  return 0;
}
