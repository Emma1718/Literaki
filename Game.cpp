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

  // while(true)
  //   {
  //     for(int i = 0; i < sizeof(this->players_tab); i++)
  //     	{
  int opt;
  bool foundAll = true;
  list <string> wordsToCheck;

   list <string>::iterator iter;

   while (!(this->players_tab[0]->move())); 
   if (Gtk::tmp_char.getChar() == '\0')
     {
       if (this->map->check_move(opt))
	 {
	   g_print("Poprawny ruch!");
       
	   this->map->find_words(&wordsToCheck, opt);
     
	   for(iter = wordsToCheck.begin();iter!=wordsToCheck.end();iter++)
	     {
	       cout<<"iter:"<<(*iter);
	       if(this->dictionary->checkWord((*iter))==true) 
		 cout<<"Found!!!"<<endl;
	       else 
		 {
		   foundAll = false;
		   break;
		 }
	     }
	   if (foundAll)
	     {
	       this->map->clearModifications();
	     }    
	 }
     }
}

