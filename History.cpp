#include "History.h"

History::History(Map *map, Sack * sack, Player *tab[])
{
  this->mapHist = new Map(*map);//Map(&map);
  this->sackHist = new Sack(*sack);
  for(int i = 0; i < 2; i++)
    this->playersHist[i] = new Player(*tab[i]);
}

// History::~History()
// {
//   //
// }

void History::saveHistory()
{
  //
}

Map* History::loadMapHist()
{
  return this->mapHist;
}


Sack* History::loadSackHist()
{
  return this->sackHist;
}

Player* History::loadPlayerHist(int which)
{
  return this->playersHist[which];
}
