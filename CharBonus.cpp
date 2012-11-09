#include "CharBonus.h"

CharBonus::CharBonus(Map * map, int a, int b, int x, int y)
{
  this->which_char = a;
  this->multiplier = b;
  this->parent = map;
  this->col_no = y;
  this->row_no = x;
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
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(Field::Click), this);
  return this->button;
}
