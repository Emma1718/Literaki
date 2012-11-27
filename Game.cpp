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
  this->players_tab[1] = new Computer("Komputer", 0, this->sack, this->dictionary, this->map, filename_sack);
  this->history.push_back(History(this->map, this->sack, this->players_tab));
  this->graphic->changebackButton(this->history.size());

  this->leftTurns = 0;
}

void Game::run()
{
  this->graphic->run();
}

void Game::process()
{
  bool foundAll = false;
  GtkWidget *dialogMessage;
  gint result;

  list <string> wordsToCheck;
  list <string>::iterator iter;

  this->map->findWords(&wordsToCheck, this->option); //znajdz wyrazy

  for(iter = wordsToCheck.begin(); iter != wordsToCheck.end(); iter++) //sprawdz je w słowniku
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
      this->players_tab[0]->removeLetters(this->insertions);  //to usun te litery, które zostały wykorzystane
      this->map->clearModAndBonus();                   //usun bonusy i modyfikacje
      this->players_tab[0]->addLetters(this->insertions.size()); //dodaj nowe litery
    }
  else //jesli nie
    {
      this->leftTurns++;
      //      dialogMessage = 
this->graphic->createDialogMessage((char*)"BŁĘDNY WYRAZ!!!", GTK_DIALOG_MODAL,GTK_BUTTONS_OK);
      
      // while (gtk_events_pending())
      // 	gtk_main_iteration();
      // sleep(1.5);

      // result = gtk_dialog_run(GTK_DIALOG (dialogMessage));
      // if(result == GTK_RESPONSE_OK)
      // 	gtk_widget_destroy(dialogMessage);

      static_cast<Human*>(this->players_tab[0])->returnLetters(this->insertions);  //to "zawróc" litery
      this->map->clearFields(); //usun je z planszy
    }
  
  this->insertions.clear(); //wyczysc listę

  this->history.push_back(History(this->map, this->sack, this->players_tab));
  this->graphic->changebackButton(this->history.size());

  if((this->players_tab[0]->getLettersAmount() == 0) || (this->leftTurns == 2*(sizeof(players_tab)/sizeof(players_tab[0]))))
    {
      this->endOfGame();
      return;
    }
 
  this->map->disableMap();	      //zdezaktywuj mape
  static_cast<Human*>(this->players_tab[0])->disableHumanBox();  // i zdezaktywuj HumanBoxa

  while (gtk_events_pending())
    gtk_main_iteration();
  sleep(1.5);

  Gtk::clockEnd();
  this->map->tmp_sum = 0; 

  this->playerNumber++; //inkrementuj nr zawodnika
  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0]))
    this->playerNumber = 0; //jesli numer jest większy od liczy zawodników, ustaw na 0
  this->automaticMove(); //przjdz to automatycznego ruchu

}

void Game::omitMove()
{
  this->leftTurns++;
  cout<<"left turns:"<<leftTurns<<"pl:"<<2*(sizeof(players_tab)/sizeof(players_tab[0]))<<endl;
  this->map->getAllInsertions(false, this->insertions);

  static_cast<Human*>(this->players_tab[0])->returnLetters(insertions);
  this->map->clearFields();

  insertions.clear();

  if(this->leftTurns == 2*(sizeof(players_tab)/sizeof(players_tab[0])))
    {
      cout<<"KONIEC"<<endl;
      this->endOfGame();
      return;
    }
  this->history.push_back(History(this->map, this->sack, this->players_tab));
  this->graphic->changebackButton(this->history.size());
 
  this->map->disableMap();	      
  static_cast<Human*>(this->players_tab[0])->disableHumanBox(); 

  while (gtk_events_pending())
    gtk_main_iteration();
  sleep(1.5);

  Gtk::clockEnd();
 
  this->playerNumber++;
  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0])) this->playerNumber = 0;
  this->automaticMove();
}

void Game::automaticMove()
{
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
	  cout<<"left turns:"<<leftTurns<<endl;
	}      
      else this->leftTurns = 0;

      this->graphic->changeActPoints(2, this->players_tab[playerNumber]->getActPoints());
      this->players_tab[playerNumber]->removeLetters(this->insertions);  //to usun te litery, które zostały wykorzystane
      this->players_tab[playerNumber]->addLetters(this->insertions.size());
      this->map->clearModAndBonus(); 
      this->map->tmp_sum = 0;
      this->insertions.clear();
    }

  this->history.push_back(History(this->map, this->sack, this->players_tab));
  this->graphic->changebackButton(this->history.size());

  this->playerNumber++;

  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0])) 
    this->playerNumber = 0;
  
  if (this->playerNumber != 0)
    this->automaticMove();
  else
    {
      this->map->enableMap();
      static_cast<Human*>(this->players_tab[0])->enableHumanBox();
      Gtk::clockStart();
    }

  if((this->players_tab[0]->getLettersAmount() == 0) || (this->leftTurns == 2*(sizeof(players_tab)/sizeof(players_tab[0]))))
    {
      this->endOfGame();
      return;
    }
}

void Game::checkifProcess()
{

  GtkWidget *dialogMessage;

  if (Gtk::tmp_char.getChar() == "") //jeśli w pamięci nie ma żadnej litery
    {
      if (this->map->checkMove(this->option)) //jeśli poprawny ruch
	{
	  if(!(this->map->getAllInsertions(true, this->insertions)))
	    this->process();
	}  //to pobierz wszystkie wstawione litery,sprawdz czy nie ma blanka,  utworz z nich listę
      else
	{
	  this->map->getAllInsertions(false, this->insertions);
	  
	  // dialogMessage = this->graphic->createDialogMessage("BŁEDNY RUCH", GTK_DIALOG_MODAL,GTK_BUTTONS_NONE);
	  // while (gtk_events_pending())
	  //   gtk_main_iteration();
	  // sleep(1.5);
	  // gtk_widget_destroy(dialogMessage);

	  static_cast<Human*>(this->players_tab[0])->returnLetters(insertions);
	  this->map->clearFields();

	  this->insertions.clear(); //wyczysc listę

	  this->map->disableMap();	      //zdezaktywuj mape
	  static_cast<Human*>(this->players_tab[0])->disableHumanBox();  // i zdezaktywuj HumanBoxa

	  while (gtk_events_pending())
	    gtk_main_iteration();
	  sleep(1.5);

	  Gtk::clockEnd();
	  
	  this->playerNumber++; //inkrementuj nr zawodnika
	  if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0]))
	    this->playerNumber = 0; //jesli numer jest większy od liczby zawodników, ustaw na 0
	  this->automaticMove(); //przjdz to automatycznego ruchu

	}
    }
  else //jesli jest w pamięci litera
    {
      // dialogMessage = this->graphic->createDialogMessage("W pamięci jest litera!\n Umieść ją na planszy lub w swoim pudełku liter!", GTK_DIALOG_MODAL,GTK_BUTTONS_NONE); 
      // while (gtk_events_pending())
      // 	gtk_main_iteration();
      // sleep(1.5);
      // gtk_widget_destroy(dialogMessage);
    }
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

  exit(0);
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

  for(int i = 0; i < sizeof(players_tab)/sizeof(players_tab[0]);i++) 
    {
      this->players_tab[i]->readPlayer(*(*it).loadPlayerHist(i)); 
      this->graphic->changeActPoints(i+1, this->players_tab[i]->getActPoints());
    }
  static_cast<Human*>(this->players_tab[0])->drawAfterBack();
}

void Game::endOfGame()
{
  int max;
  int maxP = 0;
  char winner[15];
  GtkWidget *message;
  gint result; 

  Gtk::clockEnd();

  for(int i = 0; i < sizeof(players_tab)/sizeof(players_tab[0]); i++)
    if (this->players_tab[i]->getFinalPoints() > maxP)
      {
	max = i;
	maxP = this->players_tab[i]->getFinalPoints();
	this->graphic->changeActPoints(i+1, this->players_tab[i]->getFinalPoints());
      }
  sprintf(winner, "WYGRAŁ %s", (char*)this->players_tab[max]->getName().c_str());
  
  this->graphic->createDialogMessage(winner,GTK_DIALOG_MODAL, GTK_BUTTONS_OK);
  // result = gtk_dialog_run(GTK_DIALOG(message));
  // if (result == GTK_RESPONSE_OK)
     gtk_main_quit();
}  
