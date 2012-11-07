#ifndef CHARACTER_H
#define CHARACTER_H


/// class Character - 
class Character {
  // Attributes
  char * c;
  int value;
  // Operations
public:
  Character (char* c, int value);
  Character ();
  ~Character ();
  void BacktoStart();
  int getValue ();
  char * getChar ();
};

#endif 
