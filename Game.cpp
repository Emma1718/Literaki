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
  GtkWidget *dialogMessage;

  list <string> wordsToCheck;
  list <Character> insertions;

  list <string>::iterator iter;
  list <Character>::iterator it;

  if (Gtk::tmp_char.getChar() == "") //jeśli w pamięci nie ma żadnej litery
    {
      insertions = this->map->getAllInsertions();  //to pobierz wszystkie wstawione litery, utworz z nich listę

      if (this->map->checkMove(opt)) //jeśli poprawny ruch
	{
	  g_print("poprawny ruch\n");
	  this->map->findWords(&wordsToCheck, opt); //to znajdz wyrazy

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
	      this->players_tab[0]->addPoints(Map::tmp_sum); //przekaż punkty graczowi
	      this->graphic->changeActPoints(1, this->players_tab[0]->showActPoints());
	      this->players_tab[0]->removeLetters(insertions);  //to usun te litery, które zostały wykorzystane
	      this->map->clearModAndBonus();                   //usun bonusy i modyfikacje
	      this->players_tab[0]->addLetters(insertions.size()); //dodaj nowe litery
	    }
	  else //jesli nie
	    {
	      //dialogMessage = this->graphic->createDialogMessage((char*)"Nie", GTK_DIALOG_MODAL,GTK_BUTTONS_NONE);
	      // //gtk_dialog_run (GTK_DIALOG (dialogMessage));
	      // while (gtk_events_pending())
	      // 	gtk_main_iteration();
	      // sleep(1.5);

	      // gtk_widget_destroy(dialogMessage);

	      static_cast<Human*>(this->players_tab[0])->returnLetters(insertions);  //to "zawróc" litery
	      this->map->clearFields(); //usun je z planszy
	    }
	}
      else
	{
	  dialogMessage = this->graphic->createDialogMessage("BŁEDNY", GTK_DIALOG_MODAL,GTK_BUTTONS_NONE);
	  while (gtk_events_pending())
	    gtk_main_iteration();
	  sleep(1.5);
	  gtk_widget_destroy(dialogMessage);
	  static_cast<Human*>(this->players_tab[0])->returnLetters(insertions);
	  this->map->clearFields();
	}

      insertions.clear(); //wyczysc listę

      this->map->disableMap();	      //zdezaktywuj mape
      static_cast<Human*>(this->players_tab[0])->disableHumanBox();  // i zdezaktywuj HumanBoxa

      while (gtk_events_pending())
	gtk_main_iteration();
      sleep(1.5);

      this->playerNumber++; //inkrementuj nr zawodnika
      if (this->playerNumber == sizeof(players_tab)/sizeof(players_tab[0])) this->playerNumber = 0; //jesli numer jest większy od liczy zawodników, ustaw na 0
      this->automaticMove(); //przjdz to automatycznego ruchu
    }
  else //jesli jest w pamięci litera
    {
      dialogMessage = this->graphic->createDialogMessage("W pamięci jest litera!\n Umieść ją na planszy lub w swoim pudełku liter!", GTK_DIALOG_MODAL,GTK_BUTTONS_NONE); //poinformuj usera
      while (gtk_events_pending())
	gtk_main_iteration();
      sleep(1.5);
      gtk_widget_destroy(dialogMessage);
    }
  Map::tmp_sum = 0; //wyzeruj tymczasową sumę punktów

}

void Game::omitMove()
{
  list <Character> insertions;
  insertions = this->map->getAllInsertions();

  static_cast<Human*>(this->players_tab[0])->returnLetters(insertions);
  this->map->clearFields();

  insertions.clear();

  this->map->disableMap();	      //zdezaktywuj mape
  static_cast<Human*>(this->players_tab[0])->disableHumanBox();  // i zdezaktywuj HumanBoxa

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
    {
      g_print("Automatic!\n");
    }  

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
