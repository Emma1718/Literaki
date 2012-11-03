#include "Human.h"

using namespace std;

Human::Human(string name, int points, Gtk* graphic)//, Sack *sack)
{
  // this->sack = sack;
  this->name = name;
  this->points = points;
  this->humanbox = new HumanBox(7,graphic);
}
