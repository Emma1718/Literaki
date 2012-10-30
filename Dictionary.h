#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <set>
#include <string>

class Dictionary
{

  std::set <std::string> words;

public:
  Dictionary(std::string filename_dict);
  bool checkWord(std::string word);

};

#endif
