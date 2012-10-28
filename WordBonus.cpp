#include "WordBonus.h"

WordBonus::WordBonus(int a)
{
  this->multiplier=a;
}

void WordBonus::calculate()
{
  //
}

GtkWidget *WordBonus::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button();
  graphic->ChangeColor(this->button,"grey");
  return this->button;
}
