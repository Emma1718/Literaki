#include "History.h"

History::History(Map *map)
{
  this->mapHist = new Map(*map);//Map(&map);
}

// History::~History()
// {
//   //
// }

void History::saveHistory()
{
  //
}

void History::loadHistory()
{
  this->mapHist->readMap();
}
