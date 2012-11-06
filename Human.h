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
 public :
  Human(std::string, int, Gtk *, Sack *);
  //~Human();  
  //  static void HumanChar_ButtonClicked(Gtk*, gpointer);
  void Click();
};


#endif 
