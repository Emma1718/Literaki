#ifndef HUMAN_H
#define HUMAN_H


#include "Player.h"
#include "HumanBox.h"

/// class Human - 
class Human : public Player {

  HumanBox *humanbox;
 public :
  Human(std::string name, int points,Gtk *graphic);
  //~Human();  
};


#endif 
