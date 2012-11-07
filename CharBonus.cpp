#include "CharBonus.h"

CharBonus::CharBonus(int a, int b)
{
  this->which_char = a;
  this->multiplier = b;
}

int CharBonus::calculate(int * word_multiplier)
{
  int x = this->c.getValue();
  if (x==this->which_char) return (this->multiplier)*x;
  else return x;
}
GtkWidget *CharBonus::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button((char*)"", 38, 38);
  graphic->ChangeColor(this->button, this->which_char);
  return this->button;
}
