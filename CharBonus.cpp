#include "CharBonus.h"

CharBonus::CharBonus(int a, int b)
{
  this->which_char = a;
  this->multiplier = b;
}

void CharBonus::calculate()
{
  //
}
GtkWidget *CharBonus::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button();
  switch(this->which_char)
    {
    case 1:
      graphic->ChangeColor(this->button, "yellow");
      break;
    case 2:
      graphic->ChangeColor(this->button, "green");
      break;
    case 3:
      graphic->ChangeColor(this->button,"blue");
      break;
    case 5:
      graphic->ChangeColor(this->button,"red");
      break;
    }
  return this->button;
}
