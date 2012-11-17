#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

/// class Character - 
class Character {
  // Attributes
  std::string c;
  int value;
  // Operations
public:
  Character (std::string c, int value);
  Character ();
  ~Character ();
  void backtoStart();
  int getValue ();
  std::string getChar ();
};

#endif 
