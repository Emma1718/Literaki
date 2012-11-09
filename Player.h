#ifndef PLAYER_H
#define PLAYER_H

#include "Sack.h"
#include <string>
#include <vector>
#include "Map.h"
#include "Dictionary.h"

#include <set>


/// class Player - 
class Player {
  // Attributes
protected:
  std::string name;
  int points;
  //  int left_time;
  Sack * sack;
  Dictionary * dict;
  Map * map;
  std:: vector <Character> letters;
  // Operations
public:
  virtual bool move ();
};

#endif 
