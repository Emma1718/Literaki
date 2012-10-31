#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
/// class Character - 
class Character {
  // Attributes
protected:
  char * c;
  int value;
  // Operations
public:
  Character (char* c, int value);
  Character ();
  ~Character ();
  int getValue ();
  char * getChar ();
};

#endif 
