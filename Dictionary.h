#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <set>


class Dictionary
{



public:
  std::set <std::string> words;
  Dictionary(std::string filename_dict);
  bool checkWord(std::string word);
  void ShowD();
};

#endif
