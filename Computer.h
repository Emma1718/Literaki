#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

#include <list>
/// class Computer - 
class Computer : public Player {

  std::list <Character> listOfLetters;
  void loadLettersFromFile(std::string filename);
 public:
  Computer(std::string, int,Sack *,  Dictionary *, Map *, std::string);
  //~Computer();

  bool empty(std::string line);
  char first (std::string line, int &i);
  std::string letters_and_distances(std::string line, std::list<int> &distances);  

  bool contain_letter(std::string word, std::string letter, int &left, int &right);
  std::string nth_letter(int n, std::string word);
  bool without(std::string &word, std::string letter);

  bool find(int RowOrCol, int nr, std::string letters, std::list<int> distances);
  bool findWord();

  bool findInLine(int RowOrCol, int nr, std::string &letters, std::list<int> &distances);

  std::list <Character> copy_list();
  Character fromStringToCharacter(std::string);
};

#endif 
