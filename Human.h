#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>

#include "Player.h"
#include "HumanBox.h"
#include "Sack.h"

/// class Human - 
class Human : public Player {

  HumanBox *humanbox;
  Sack * sack;
  static bool commited;  
 public :

  Human(std::string, int, Gtk *, Sack *, Map *);
  //~Human();  
  //  static void HumanChar_ButtonClicked(Gtk*, gpointer);
 static void SetCommit();

  void addLetters(int);
};


#endif 
