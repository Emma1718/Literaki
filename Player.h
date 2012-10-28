#ifndef PLAYER_H
#define PLAYER_H

/// class Player - 
class Player {
  // Attributes
protected:
  string name;
  int points;
  Sack * sack;
  // Operations
public:
  bool move ();
};

#endif 
