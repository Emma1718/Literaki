#include "Map.h"
#include <iostream>
using namespace std;

Field::Field(Map * parent, Gtk * graphic, int x, int y)
{
  this->c = Character();
  this->graphic = graphic;
  this->row_no = x;
  this->col_no = y;
  this->parent = parent;
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
  //  g_signal_connect(this->button, "enter", GTK_SIGNAL_FUNC(Field::Enter), this);
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
  //  g_print("%d %d", this->row_no, this->col_no);
 
 if (Gtk::tmp_char.getChar() == '\0')
    {
      // this->graphic->ChangeColor(button, 0);
      // this->graphic->setLabel(button, (char*)"");
      // this->clicked = true;
      // static_cast<HumanBox*>(this->parent)->DisableHumanChars();
      // static_cast<HumanBox*>(this->parent)->ChangeActualLetter(this->letter.getValue(), this->letter.getChar());
      // Gtk::tmp_char = this->letter;
      // this->letter.BacktoStart();
}
  else 
    {
      this->insert(Gtk::tmp_char);
      Gtk::tmp_char.BacktoStart();
      this->graphic->ChangeActualLetter(0, (char*)"");     
      this->graphic->setLabel(this->button, this->c.getChar());
      this->graphic->ChangeColor(this->button, this->c.getValue());
      //      static_cast<HumanBox*>(this->parent)->EnableHumanChars();
    }

}

// void Field::Enter(void * widget, gpointer data)
// {
//   Field * f = static_cast<Field*>(data);
//   f->ButtonEnterEvent();
// }

// void Field::ButtonEnterEvent()
// {
//   if (Gtk::tmp_char.getChar()!='\0')
//     {
//       this->graphic->setLabel(this->button, (Gtk::tmp_char).getChar());
//       this->graphic->ChangeColor(this->button, (Gtk::tmp_char).getValue());
//     }
// }
