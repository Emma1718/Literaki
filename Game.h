#ifndef GAME_H
#define GAME_H

/* #include "Sack.h" */
#include "Map.h"
#include "Gtk.h"
#include "Player.h" 
#include "Dictionary.h"
#include "Human.h"
#include "Computer.h"

#include <string>
#include <iostream>



/// class Game -
class Game {
  // Associations
  Sack* sack;
  Gtk* graphic;
  Map* map;
  int playerNumber;
  Player *players_tab[2];
  Dictionary* dictionary;
  // Operations
 public:
  Game (int argc, char *argv[],std::string filename_matrix, std::string filename_sack, std::string filename_dict);
  //~Game ();
  void  run ();
  void process();
  void omitMove();
  void automaticMove();
};

#endif
