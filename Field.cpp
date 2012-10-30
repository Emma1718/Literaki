#include "Field.h"

using namespace std;

Field::Field()
{
  this->multiplier = 1;
}

int Field::calculate()
{
  int x = this->c.getValue();
  return x;
}
GtkWidget * Field::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button();
  graphic->ChangeColor(this->button,"white");
  return this->button;
}
