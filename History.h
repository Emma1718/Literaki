#ifndef HISTORY
#define HISTORY

#include "Map.h"
#include "Player.h"
#include "Sack.h"

class History {

  Map *mapHist;
  Player *playersHist[2];
  Sack *sackHist;

 public:

  History(Map*);
  //  ~History();
  void saveHistory();
  void loadHistory();

};

#endif
