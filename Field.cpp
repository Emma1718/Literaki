#include "Field.h"
#include <iostream>
using namespace std;

Field::Field()
{
  this->c = Character();
}

int Field::calculate()
{
  int x = this->c.getValue();
  return x;
}
GtkWidget * Field::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button("", 38, 38);
  graphic->ChangeColor(this->button,"white");
  return this->button;
}
void Field::insert(Character c)
{
  this->c = c;
  gtk_button_set_label(GTK_BUTTON(this->button), this->c.getChar());
}
