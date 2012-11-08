#include "Map.h"
#include <iostream>
using namespace std;

Field::Field(void * parent)
{
  this->c = Character();
  this->parent = static_cast<Map*>(parent);
}

int Field::calculate(int * word_multiplier)
{
  int x = this->c.getValue();
  return x;
}
GtkWidget * Field::draw(Gtk *graphic)
{
  this->button = graphic->Create_Button((char*)"", 38, 38);
  graphic->ChangeColor(this->button,0);
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(Field::Click), this);
  return this->button;
}
void Field::insert(Character c)
{
  this->c = c;
}

void Field::Click(void * widget, gpointer data)
{
  Field *f = static_cast<Field*>(data);
  f->ButtonClickedEvent();

}
Field::Field()
{
  //
}

void Field::ButtonClickedEvent()
{
  int i, j;
  this = &(static_cast<Map*>(this->parent)->matrix[i][j]);
  g_print("%d %d", i, j);
}
