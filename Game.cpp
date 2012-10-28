#include "Game.h"

using namespace std;

Game::Game(int argc, char *argv[])
{
  this->graphic = new Gtk(argc, argv);
  this->map = new Map(this->graphic);
}

void Game::run()
{
  this->graphic->run();
}
