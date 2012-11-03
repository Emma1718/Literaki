#ifndef HUMAN_H
#define HUMAN_H


#include "Player.h"
#include "HumanBox.h"
#include "Sack.h"

/// class Human - 
class Human : public Player {

  HumanBox *humanbox;
  Sack * sack;
 public :
  Human(std::string name, int points,Gtk *graphic);//, Sack *sack);
  //~Human();  
};


#endif 
