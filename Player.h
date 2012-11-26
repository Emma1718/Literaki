#ifndef PLAYER_H
#define PLAYER_H

#include "Sack.h"
#include "Map.h"
#include "Dictionary.h"

#include <string>
#include <list>

/// class Player - 
class Player {
  // Attributes
 protected:
  std::string name;
  int points;
  Sack * sack;
  Dictionary * dict;
  Map * map;
  std:: list <Character> letters;
  // Operations
public:
  void removeLetters(std::list <Character>);
  virtual void addLetters(int); 
  void addPoints(int);
  int getActPoints();
  int getLettersAmount();
  virtual ~Player();
  Player(Player &);
  Player();
  void readPlayer(Player &);
};
#endif 
