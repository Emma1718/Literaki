#include "Game.h"

using namespace std;

Game::Game(int argc, char *argv[], string filename)
{
  this->graphic = new Gtk(argc, argv);
  this->map = new Map(this->graphic,filename);
}

void Game::run()
{
  this->graphic->run();
}
