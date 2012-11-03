#include "Game.h"
using namespace std;

int main(int argc, char * argv[])
{
  Game game(argc, argv,"matrix", "slowa","litery");
  game.run();
  // Dictionary dict;
  // dict.load("plik.txt");
  // dict.checkWord("ktury"); //false
  // dict.checkWord("ser") //true
  return 0;
}
