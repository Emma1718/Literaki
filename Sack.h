#ifndef SACK_H
#define SACK_H

#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
//#include <vector>
#include <list>
#include "Character.h"

/// class Sack - 
class Sack {

  std::map <int,Character> characters;
  int size;
 public:

  Sack(std::string filename_sack);
  Sack (Sack &);
  ~Sack();
  //  std::string
  int getCharacters(std::list <Character> *letters, int  amount);
  void show();
  void readSack(Sack &);
};

#endif 
