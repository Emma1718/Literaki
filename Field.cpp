#include "Field.h"
#include <iostream>
using namespace std;

Field::Field()
{
  this->c = Character();
}

int Field::calculate(int * word_multiplier)
{
  int x = this->c.getValue();
  return x;
}
GtkWidget * Field::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button((char*)"", 38, 38);
  graphic->ChangeColor(this->button,(char*)"white");
  //  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(graphic->Click), (*this));
  return this->button;
}
void Field::insert(Character c)
{
  this->c = c;
  gtk_button_set_label(GTK_BUTTON(this->button), this->c.getChar());
}

// void Field::Click()
// {
//   //
// }
