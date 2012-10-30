#ifndef PLAYER_H
#define PLAYER_H

#include "Sack.h"
#include <string>

/// class Player - 
class Player {
  // Attributes
protected:
  std::string name;
  int points;
  Sack * sack;
  // Operations
public:
  bool move ();
};

#endif 
