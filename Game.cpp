 #include "Game.h"

using namespace std;

Game::Game(int argc, char *argv[], string filename_matrix, string filename_sack, string filename_dict)
{

  this->graphic = new Gtk(argc, argv,this);
  this->map = new Map(this->graphic,filename_matrix);
  this->sack = new Sack(filename_sack);
  this->dictionary = new Dictionary(filename_dict);
  this->players_tab[0] = new Human("Gracz", 0, this->graphic, this->sack, this->map);
  this->players_tab[1] = new Computer("Komputer", 0, this->sack, this->dictionary, this->map, filename_sack);

  this->history.push_back(History(this->map, this->sack, this->players_tab));
  this->graphic->changebackButton(this->history.size());

  this->leftTurns = 0;
  this->playerNumber = 0;
}

void Game::run()
{
  this->graphic->run();
}

void Game::process()
{
  bool foundAll = false;
 
  list <string> wordsToCheck;
  list <string>::iterator iter;

  this->map->findWords(&wordsToCheck, this->option);

  for(iter = wordsToCheck.begin(); iter != wordsToCheck.end(); iter++) 
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
      this->leftTurns = 0;
      this->players_tab[0]->addPoints(this->map->tmp_sum); //przekaż punkty graczowi
      this->graphic->changeActPoints(1, this->players_tab[0]->getActPoints());
      this->players_tab[0]->removeLetters(this->insertions); 
      this->map->clearModAndBonus();                  
      this->players_tab[0]->addLetters(this->insertions.size()); 
    }
  else 
    {
      this->mistake("NIE MA TAKIEGO WYRAZU!");
    }
  

  if((this->players_tab[0]->getLettersAmount() == 0) || (this->leftTurns == 2*(sizeof(players_tab)/sizeof(players_tab[0]))))
    {
      this->endOfGame();
      return;
    }

  this->insertions.clear(); 

  this->history.push_back(History(this->map, this->sack, this->players_tab));
  this->graphic->changebackButton(this->history.size());

  this->disableHumanPart();

  while (gtk_events_pending())
    gtk_main_iteration();
  sleep(1.5);

  this->map->tmp_sum = 0; 

  this->playerNumber++;
  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0]))
    this->playerNumber = 0; 
  this->automaticMove(); 

}

void Game::omitMove()
{
  if (Gtk::tmp_char.getChar() == "")
    {
      this->map->getAllInsertions(false, this->insertions);
      this->mistake("STRATA KOLEJKI!");
      insertions.clear();

      if(this->leftTurns == 2*(sizeof(players_tab)/sizeof(players_tab[0])))
	{
	  this->endOfGame();
	  return;
	}

      this->history.push_back(History(this->map, this->sack, this->players_tab));
      this->graphic->changebackButton(this->history.size());
 
      this->disableHumanPart();

      while (gtk_events_pending())
	gtk_main_iteration();
      sleep(1.5);
 
      this->playerNumber++;
      if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0])) this->playerNumber = 0;
      this->automaticMove();
    }
  else 
    this->graphic->createDialogMessage((char*)"W pamięci jest litera!\nUmieść ją na planszy lub w swoim\npudełku liter!"); 
}

void Game::automaticMove()
{
  int actPl = this->playerNumber;

  if (this->playerNumber > 0)
    {
      if(this->map->isEmpty())
	static_cast<Computer*>(this->players_tab[playerNumber])->findIfEmpty();
      else   
	static_cast<Computer*>(this->players_tab[playerNumber])->findWord();

      this->map->getAllInsertions(false, this->insertions);
      
      if(this->insertions.size() == 0) 
	{
	  this->leftTurns++;
	  this->graphic->createDialogMessage((char*)"KOMPUTER PASUJE!!!");
	}
      else
	{
	  this->leftTurns = 0;

	  this->graphic->changeActPoints(2, this->players_tab[playerNumber]->getActPoints());
	  this->players_tab[playerNumber]->removeLetters(this->insertions);  //to usun te litery, które zostały wykorzystane
	  this->players_tab[playerNumber]->addLetters(this->insertions.size());
	  this->map->clearModAndBonus(); 
	  this->map->tmp_sum = 0;
	  this->insertions.clear();
	}
    }

  this->history.push_back(History(this->map, this->sack, this->players_tab));
  this->graphic->changebackButton(this->history.size());

  this->playerNumber++;

  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0])) 
    this->playerNumber = 0;


   if((this->players_tab[actPl]->getLettersAmount() == 0) || (this->leftTurns == 2*(sizeof(players_tab)/sizeof(players_tab[0]))))
    {
      this->map->enableMap();
      this->endOfGame();
      return;
    } 

  if (this->playerNumber != 0)
    this->automaticMove();
  else
    {
      this->map->enableMap();
      static_cast<Human*>(this->players_tab[0])->enableHumanBox();
      this->graphic->changebackButton(2);
      Gtk::clockStart();
    }
  
}

void Game::checkifProcess()
{
  if (Gtk::tmp_char.getChar() == "")
    {
      if (this->map->checkMove(this->option)) 
	{
	  if(!(this->map->getAllInsertions(true, this->insertions)))
	    this->process();
	} 
      else
	{
	  this->map->getAllInsertions(false, this->insertions);
	  this->mistake("BŁĘDNY RUCH");
	  this->insertions.clear(); 
 
	  if(this->leftTurns == 2*(sizeof(players_tab)/sizeof(players_tab[0])))
	    {
	      this->endOfGame();
	      return;
	    } 
	  this->disableHumanPart();

	  while (gtk_events_pending())
	    gtk_main_iteration();
	  sleep(1.5);
	  
	  this->playerNumber++; 
	  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0]))
	    this->playerNumber = 0;
	  this->automaticMove(); 

	}
    }
  else 
    {
      this->graphic->createDialogMessage((char*)"W pamięci jest litera!\n Umieść ją na planszy\n lub w swoim pudełku liter!"); 
    }
}

void Game::disableHumanPart()
{
  this->map->disableMap();	      
  static_cast<Human*>(this->players_tab[0])->disableHumanBox(); 
  this->graphic->changebackButton(1);
  Gtk::clockEnd();
}

void Game::mistake(string message)
{
  this->leftTurns++;
  this->graphic->createDialogMessage((char*)message.c_str());
 
  static_cast<Human*>(this->players_tab[0])->returnLetters(this->insertions);
  this->map->clearFields();
}

Game::~Game()
{
  for(int i = 0; i < this->playerNumber; i++)
    delete this->players_tab[i];

  this->insertions.clear();
  delete this->dictionary;
  delete this->sack;
  delete this->map;
  delete this->graphic;
  this->history.clear();
}

void Game::backInHistory()
{
  list <History>::reverse_iterator it;  
 
  Gtk::tmp_char.backtoStart();
  this->graphic->changeActLetter(0, "");

  this->history.pop_back();
  if (this->history.size() == 1)
    this->graphic->changebackButton(1);

  it = this->history.rbegin();
  this->map->readMap(*((*it).loadMapHist()));
  this->map->drawAfterBack();

  this->sack->readSack(*(*it).loadSackHist());

  for(int i = 0; i < (int) (sizeof(players_tab)/sizeof(players_tab[0]));i++) 
    {
      this->players_tab[i]->readPlayer(*(*it).loadPlayerHist(i)); 
      this->graphic->changeActPoints(i+1, this->players_tab[i]->getActPoints());
    }
  static_cast<Human*>(this->players_tab[0])->drawAfterBack();
}

void Game::endOfGame()
{
  int max;
  int maxP = -35;
  char winner[120];

  Gtk::clockEnd();

  for(int i = 0; i <(int)(sizeof(players_tab)/sizeof(players_tab[0])); i++)
    {
      if (this->players_tab[i]->getFinalPoints() > maxP)
	{
	  max = i;
	  maxP = this->players_tab[i]->getFinalPoints();
	}
      this->graphic->changeActPoints(i+1, this->players_tab[i]->getFinalPoints());
    }

  if(this->leftTurns == 2*(int)(sizeof(players_tab)/sizeof(players_tab[0])))
    sprintf(winner, "GRACZE OMINĘLI PO 2 KOLEJKI\nWYGRAŁ %s\nZDOBYŁ %d PUNKTÓW\n", (char*)this->players_tab[max]->getName().c_str(), this->players_tab[max]->getFinalPoints());
  else
    sprintf(winner, "BRAK LITER W WORKU I W PUDEŁKU\n JEDNEGO Z GRACZY!\nWYGRAŁ %s\nZDOBYŁ %d PUNKTÓW\n", (char*)this->players_tab[max]->getName().c_str(), this->players_tab[max]->getFinalPoints());

  this->graphic->createDialogMessage(winner);
     gtk_main_quit();
}  
