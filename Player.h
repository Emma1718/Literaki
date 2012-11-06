#ifndef PLAYER_H
#define PLAYER_H

#include "Sack.h"
#include <string>
#include <vector>
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
  std:: vector <Character> letters;
  // Operations
public:
  bool move ();
};

#endif 
