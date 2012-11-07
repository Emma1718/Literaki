#include "WordBonus.h"

WordBonus::WordBonus(int a)
{
  this->multiplier=a;
}

int WordBonus::calculate(int * word_multiplier)
{
  *word_multiplier = this->multiplier;
  int x = this->c.getValue();
  return x;
}

GtkWidget *WordBonus::draw(Gtk *graphic)
{
  char * str = new char[10];
  int x = this->multiplier;
  sprintf(str, "%dx", x);
  this->button = graphic->Create_Button(str, 38, 38);
  graphic->ChangeColor(this->button, 10);
  return this->button;
}
