#include "Game.h"

using namespace std;

Game::Game(int argc, char *argv[], string filename_matrix, string filename_sack, string filename_dict)
{
  this->graphic = new Gtk(argc, argv);//stworzenie grafiki
  this->map = new Map(this->graphic,filename_matrix);//plansza 
  this->sack = new Sack(filename_sack); 
  this->dictionary = new Dictionary(filename_dict);//wczytanie słów ze słownika
  this->players_tab[0] = new Human("Gracz", 0, this->graphic, this->sack, this->map);
  this->players_tab[1] = new Computer("Komputer", 0, this->sack, this->dictionary, this->map);

}

void Game::run()
{

  this->graphic->run();

  while(true)
    {
      for(int i = 0; i < sizeof(this->players_tab); i++)
      	{
	  while (!(this->players_tab[i]->move())); 
	  if (this->map->check_move()) g_print("Poprawny ruch!\n");
	  else g_print("Niepoprawny ruch!\n");
    	}
    }
}

