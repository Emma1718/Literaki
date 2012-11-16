#include "Game.h"
using namespace std;

Game::Game(int argc, char *argv[], string filename_matrix, string filename_sack, string filename_dict)
{
  this->graphic = new Gtk(argc, argv,this);//stworzenie grafiki
  this->map = new Map(this->graphic,filename_matrix);//plansza 
  this->sack = new Sack(filename_sack); 
  this->dictionary = new Dictionary(filename_dict);//wczytanie słów ze słownika
  this->players_tab[0] = new Human("Gracz", 0, this->graphic, this->sack, this->map);
  this->players_tab[1] = new Computer("Komputer", 0, this->sack, this->dictionary, this->map);
}

void Game::run()
{
  
  this->graphic->run();

}

void Game::process()
{
  int opt;
  bool foundAll = false;
  list <string> wordsToCheck;
  list <Character> insertions;

  list <string>::iterator iter;
  list <Character>::iterator it;


  if (Gtk::tmp_char.getChar() == '\0')
    {
      if (this->map->check_move(opt))
	{       
	  this->map->find_words(&wordsToCheck, opt);
     
	  for(iter = wordsToCheck.begin();iter!=wordsToCheck.end();iter++)
	    {
	      if(this->dictionary->checkWord((*iter))==true) 
		foundAll = true;
	      else 
		{
		  foundAll = false;
		  break;
		}
	    }
	  if (foundAll)
	    {
	      insertions = this->map->getAllInsertions();
	      this->players_tab[0]->removeLetters(insertions);

	      this->map->clearModAndBonus();
	      this->players_tab[0]->addLetters(insertions.size());
	      this->map->disableMap();	      
	    }    
	}
    }
}
