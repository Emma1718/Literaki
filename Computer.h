#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

/// class Computer - 
class Computer : public Player {

 public:
  Computer(std::string, int,Sack *,  Dictionary *, Map *);
  //~Computer();
      
  //znajduje slowo z podanych liter
  void findWord(std::string sack, std::string letter, int left, int right);

  //sprawdza czy slowo zawiera litere i zlicza ile liter jest po jej prawej a ile po lewej stronie
  bool contain_letter(std::string word, std::string letter, int &left, int &right);

  //prawda, slowo bez podanej litery jezeli slowo taka zawiera
  bool without(std::string &word, std::string letter);
  //~Computer();
};

#endif 
