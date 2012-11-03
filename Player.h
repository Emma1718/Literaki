#ifndef PLAYER_H
#define PLAYER_H

#include "Sack.h"
#include <string>
#include <vector>

/// class Player - 
class Player {
  // Attributes
protected:
  std::string name;
  int points;
  Sack * sack;
  std:: vector <Character> letters;
  // Operations
public:
  bool move ();
};

#endif 
