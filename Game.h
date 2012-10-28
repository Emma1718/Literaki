#ifndef GAME_H
#define GAME_H

/* #include "Sack.h" */
#include "Map.h"
#include "Gtk.h" 
/* #include "Player.h" */
/* #include  "Dictionary.h" */ 
#include <stdlib.h>
#include <iostream>
#include <gtk/gtk.h>
 

/// class Game - 
class Game {
  // Associations
  /* Sack* unnamed; */
   Gtk* graphic; 
   Map* map; 
  /* Player* unnamed; */
  /* Dictionary* unnamed; */
  // Operations
public:
   Game (int argc, char *argv[]);
  //~Game ();
   void  run ();
};

#endif 
