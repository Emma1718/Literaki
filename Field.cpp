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
 
  if (Gtk::tmp_char.getChar() == '\0')  //jeśli w pamięci nie ma żadnej litery
    {
      if ((this->c.getChar() != '\0') && (this->parent->check_if_modified(this->row_no, this->col_no))) // i jeśli jest litera na polu oraz to pole jest modyfikowalne
	{
	  this->graphic->ChangeColor(this->button, 0);
	  this->graphic->setLabel(this->button, (char*)"");
	  this->graphic->ChangeActualLetter(this->c.getValue(), this->c.getChar());  
	  Gtk::tmp_char = this->c;// to pobierz literę z pola i ją zapamiętaj
	  this->c.BacktoStart();
	  this->parent->modify_field(this->row_no, this->col_no, false); // a także ustaw pole niezmodyfikowanym
	}
    }
  else // jeśli jest litera w pamięci
    {
      if (this->c.getChar() != '\0')// i jeśli jest litera na polu 
	{
	  if (this->parent->check_if_modified(this->row_no, this->col_no)) // i jeśli to pole jest modyfikowalne
	    {
	      Character exchange;
	      
	      exchange = this->c;
	      this->insert(Gtk::tmp_char);  // to zamień litery
	      Gtk::tmp_char = exchange;
	  
	      this->graphic->ChangeActualLetter(Gtk::tmp_char.getValue(), Gtk::tmp_char.getChar());
	      this->graphic->setLabel(this->button, this->c.getChar());
	      this->graphic->ChangeColor(this->button, this->c.getValue());
	    }
	}
      else // jeśli nie ma litery na polu
	{
	  this->insert(Gtk::tmp_char);  // to wstaw literę
	  Gtk::tmp_char.BacktoStart();
	  this->graphic->ChangeActualLetter(0, (char*)"");     
	  this->graphic->setLabel(this->button, this->c.getChar());
	  this->graphic->ChangeColor(this->button, this->c.getValue());
	  this->parent->modify_field(this->row_no, this->col_no, true);
	}
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
