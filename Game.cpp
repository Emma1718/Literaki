#include "Game.h"
using namespace std;

Game::Game(int argc, char *argv[], string filename_matrix, string filename_sack, string filename_dict)
{
  this->playerNumber = 0;
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
      if (this->map->check_move(opt)) //jeśli poprawny ruch
	{       
	  g_print("poprawny ruch\n");
	  this->map->find_words(&wordsToCheck, opt); //to znajdz wyrazy
     
	  for(iter = wordsToCheck.begin();iter!=wordsToCheck.end();iter++) //sprawdz je w słowniku
	    {
	      if(this->dictionary->checkWord((*iter))==true) 
		foundAll = true;
	      else 
		{
		  foundAll = false;
		  break;
		}
	    }
	  if (foundAll)  //jesli te wyrazy znajdują sie w słowniku
	    {
	      insertions = this->map->getAllInsertions();
	      this->players_tab[0]->removeLetters(insertions);  //to usun te litery, które zostały wykorzystane

	      this->map->clearModAndBonus();                   //usun bonusy i modyfikacje
	      this->players_tab[0]->addLetters(insertions.size()); //dodaj nowe litery
	      this->map->disableMap();	      //zdezaktywuj mape
	      static_cast<Human*>(this->players_tab[0])->disableHumanBox();  // i zdezaktywuj HumanBoxa
	    }    
	}
      else g_print("niepoprawny\n");    
}

  while (gtk_events_pending())
    gtk_main_iteration();
  sleep(1.5);


  this->playerNumber++;
  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0])) this->playerNumber = 0;
  this->automaticMove();


}

void Game::automaticMove()
{
  if (this->playerNumber > 0)
    g_print("Automatic!\n");
  this->playerNumber++; 

  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0])) this->playerNumber = 0;
  
  if (this->playerNumber != 0)
    this->automaticMove();

  else 
    {
      this->map->enableMap();
      static_cast<Human*>(this->players_tab[0])->enableHumanBox();
    }
}
