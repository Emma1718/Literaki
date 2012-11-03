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
  switch(this->which_char)
    {
    case 1:
      graphic->ChangeColor(this->button, (char*)"yellow");
      break;
    case 2:
      graphic->ChangeColor(this->button, (char*)"DarkOliveGreen3");
      break;
    case 3:
      graphic->ChangeColor(this->button,(char*)"SteelBlue");
      break;
    case 5:
      graphic->ChangeColor(this->button,(char*)"tomato");
      break;
    }
  return this->button;
}
