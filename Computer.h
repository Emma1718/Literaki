#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

/// class Computer - 
class Computer : public Player {

 public:
  Computer(std::string name, int points, Sack * sack, Dictionary * dict);
  //~Computer();
};

#endif 
