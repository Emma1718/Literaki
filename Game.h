#ifndef GAME_H
#define GAME_H

/* #include "Sack.h" */
#include "Map.h"
#include "Gtk.h"
#include "Player.h" 
#include "Dictionary.h"
#include "Human.h"
#include "Computer.h"
#include "History.h"
#include <string>
#include <iostream>

//class History;

/// class Game -
class Game {
  // Associations
  Sack* sack;//wskaźnik na worek
  Gtk* graphic;//wskaźnik na grafikę
  Map* map;//wskaźnika na mapę
  int playerNumber; //liczba graczy
  Player *players_tab[2]; //tablica graczy
  Dictionary* dictionary;//wskaźnik na słownik
  std::list <History> history;
  std::list <Character> insertions; //lista z wszystkimi literami wstawionymi podczas danego ruchu
  int option; //opcja - czy głowny wyraz znajduje się w kolumnie czy też w wierszu
 // Operations
 public:
  Game (int argc, char *argv[],std::string filename_matrix, std::string filename_sack, std::string filename_dict); 
  ~Game ();
  void run (); //rozpoczęcie gry
  void process(); //główna funkcja obsługująca ruch gracza
  void checkifProcess(); //sprawdzenie czy można szukać wyrazu
  void omitMove(); //funkcja wywoływana po wciśniećiu PAS
  void automaticMove(); //wywołanie ruchu automatycznego komputera
  void dispose(); //zwalnianie pamięci
  int getPlNumber();
};

#endif
