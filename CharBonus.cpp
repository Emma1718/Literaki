#include "CharBonus.h"

using namespace std;

CharBonus::CharBonus(Map * map, int a, int b, int x, int y)
{

  this->c = Character();
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
  this->button = graphic->createButton((char*)"", 38, 38);
  graphic->changeColor(this->button, this->which_char);
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(Field::clickButton), this);
  return this->button;
}
void CharBonus::backToStandart()
{
  this->c.backtoStart();
  this->changeButton();
}

void CharBonus::changeButton()
{
  if(this->c.getChar() != "")
    {
      this->graphic->changeColor(this->button, this->c.getValue());
      this->graphic->setLabel(this->button, this->c.getChar());
    }
  else 
    {
      this->graphic->changeColor(this->button, this->which_char);
      this->graphic->setLabel(this->button, (char*)"");
    }
}

void CharBonus::looseBonus()
{
  this->multiplier = 1;
}

CharBonus::~CharBonus()
{
  //
}

CharBonus::CharBonus(const CharBonus & chB)
{
  this->c = chB.c;
  this->multiplier = chB.multiplier;
  this->which_char = chB.which_char;
}

void CharBonus::copyData(Field &f)
{
  this->c = static_cast<CharBonus&>(f).c;
  this->multiplier = static_cast<CharBonus&>(f).multiplier; 
  this->which_char = static_cast<CharBonus&>(f).which_char; 
}
