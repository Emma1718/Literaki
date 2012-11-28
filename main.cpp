#include "Game.h"
using namespace std;

int main(int argc, char * argv[])
{
  try
    {
      Game game(argc, argv,"matrix","litery","slowa");
      game.run();
    }
  catch(string ex)
    {
      cout<<"Exception: "<<ex<<endl;
    }
  return 0;
}
