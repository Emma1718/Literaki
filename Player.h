#ifndef PLAYER_H
#define PLAYER_H

#include "Sack.h"
#include <string>
//#include <vector>
#include <list>
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

  // Operations
public:

  std:: list <Character> letters;
  virtual bool move ();
  void removeLetters(std::list <Character>);
  virtual void addLetters(int); 
};
#endif 
