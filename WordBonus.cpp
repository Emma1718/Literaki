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
  this->button = graphic->Create_Button((char*)"", 38, 38);
  graphic->ChangeColor(this->button,(char*)"grey");
  return this->button;
}
