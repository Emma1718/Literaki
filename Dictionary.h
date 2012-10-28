#ifndef DICTIONARY_H
#define DICTIONARY_H

/// class Dictionary - 
class Dictionary {
  // Attributes
protected:
  map <char> words;
  // Operations
public:
  Dictionary (string fileName);
  ~Dictionary ();
  bool checkWord (string word);
};

#endif 

