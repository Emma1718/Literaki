#include "Field.h"

using namespace std;

Field::Field()
{
  this->multiplier = 1;
}

void Field::calculate()
{
  //
}
GtkWidget * Field::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button();
  graphic->ChangeColor(this->button,"white");
  return this->button;
}
