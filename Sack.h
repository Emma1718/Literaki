#ifndef SACK_H
#define SACK_H


/// class Sack - 
class Sack {
  // Attributes
protected:
  /// STLowa lista
  list <Character> characters;
  // Operations
public:
  Sack ();
  ~Sack ();
  int getCharacters (char * buffer, int amount);
};

#endif 
