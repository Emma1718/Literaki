#ifndef GAME_H
#define GAME_H


#include "Map.h"
#include "Gtk.h"
#include "Player.h" 
#include "Dictionary.h"
#include "Human.h"
#include "Computer.h"
#include "History.h"
#include <string>
#include <iostream>

#define PLAYERS 2
class Game {

  Sack* sack;
  Gtk* graphic;
  Map* map;
  Dictionary* dictionary;
  std::list <History> history;

  int playerNumber; //liczba graczy
  Player *players_tab[PLAYERS]; //tablica graczy

  std::list <Character> insertions; //lista z wszystkimi literami wstawionymi podczas danego ruchu
  int option; //opcja - czy głowny wyraz znajduje się w kolumnie czy też w wierszu
  int leftTurns;//stracone kolejki

 public:
  Game (int argc, char *argv[],std::string filename_matrix, std::string filename_sack, std::string filename_dict); 
  ~Game ();

  void run (); //rozpoczęcie gry
  void process(); //główna funkcja obsługująca ruch gracza
  void checkifProcess(); //sprawdzenie czy można szukać wyrazu
  void omitMove(); //funkcja wywoływana po wciśniećiu PAS
  void automaticMove(); //wywołanie ruchu automatycznego komputera
  void backInHistory();
  void endOfGame();
  void disableHumanPart();
  void mistake(std::string);
};

#endif
