#ifndef SACK_H
#define SACK_H

#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "Character.h"

/// class Sack - 
class Sack {

  std::map <int,Character> characters;

 public:
  Sack(std::string filename_sack);
  ~Sack();
  std::string getCharacters(int  amount);

};

#endif 
