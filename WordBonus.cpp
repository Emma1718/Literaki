#include "WordBonus.h"

WordBonus::WordBonus(Map * map, int a, int x, int y)
{
  this->c = Character();
  this->multiplier=a;
  this->parent = map;
  this->col_no = y;
  this->row_no = x;
}

int WordBonus::calculate(int * word_multiplier)
{
  *word_multiplier *= this->multiplier;
  int x = this->c.getValue();
  return x;
}

GtkWidget *WordBonus::draw(Gtk *graphic)
{
  char * str = new char[10];
  int x = this->multiplier;
  sprintf(str, "%dx", x);
  this->button = graphic->createButton(str, 38, 38);
  graphic->changeColor(this->button, 10);
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(Field::clickButton), this);
  return this->button;
}

void WordBonus::backToStandart()
{
  char * str = new char[10];
  int x = this->multiplier;
  sprintf(str, "%dx", x);
  this->graphic->setLabel(this->button, str);
  graphic->changeColor(this->button, 10);
  this->c.backtoStart();
}

void WordBonus::looseBonus()
{
  this->multiplier = 1;
}
