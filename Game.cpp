#include "Game.h"

using namespace std;

Game::Game(int argc, char *argv[], string filename_matrix, string filename_dict , string filename_sack)
{
  this->graphic = new Gtk(argc, argv);//stworzenie grafiki
  this->map = new Map(this->graphic,filename_matrix);//plansza 
  this->sack = new Sack(filename_sack); 
  this->dictionary = new Dictionary(filename_dict);//wczytanie słów ze słownika
  this->human = new Human("Gracz", 0, this->graphic, this->sack);//gracz - człowiek
  this->computer = new Computer("Komputer", 0, this->sack, this->dictionary);//gracz - komputer


}

void Game::run()
{
  this->graphic->run();
}
