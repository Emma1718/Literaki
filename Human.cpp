#include "Human.h"

using namespace std;

Human::Human(string name, int points, Gtk* graphic)
{
  this->name = name;
  this->points = points;
  this->humanbox = new HumanBox(7,graphic);
}
