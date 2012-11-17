#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

#include <list>

/// class Computer - 
class Computer : public Player {

 public:
  Computer(std::string, int,Sack *,  Dictionary *, Map *);
  //~Computer();

  bool empty(std::string line);
  char first (std::string line, int &i);
  std::string letters_and_distances(std::string line, std::list<int> &distances);  

  bool contain_letter(std::string word, std::string letter, int &left, int &right);
  std::string nth_letter(int n, std::string word);
  bool without(std::string &word, std::string letter);

  void find(std::string letters, std::list<int> distances, std::string comp_letters);
  void findWord(std::string line, std::string letters);

};

#endif 
