#include "WordBonus.h"

WordBonus::WordBonus(int a)
{
  this->multiplier=a;
}

int WordBonus::calculate()
{
  int x = this->c.getValue();
  return x;
}

GtkWidget *WordBonus::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button();
  graphic->ChangeColor(this->button,"grey");
  return this->button;
}
