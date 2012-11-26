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

Field::Field()
{
  this->c = Character();
}

Field::Field(const Field & f)
{
  cout<<"FieldConsturctor"<<endl;
  this->c = f.c;
}

int Field::calculate(int * word_multiplier)
{
  int x = this->c.getValue();
  return x;
}

GtkWidget * Field::draw(Gtk *graphic)
{
  this->button = graphic->createButton((char*)"", 38, 38);
  graphic->changeColor(this->button,0);
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(Field::clickButton), this);
  //  g_signal_connect(this->button, "enter", GTK_SIGNAL_FUNC(Field::Enter), this);
  return this->button;
}

void Field::insert(Character c)
{
  this->c = c;
}

void Field::clickButton(void * widget, gpointer data)
{
  Field *f = static_cast<Field*>(data);
  f->buttonClickedEvent();
}

void Field::backToStandart()
{
  this->c.backtoStart();
  this->changeButton();
}

void Field::changeButton()
{
  this->graphic->setLabel(this->button, this->c.getChar());
  this->graphic->changeColor(this->button, this->c.getValue());
}

void Field::buttonClickedEvent()
{
  //  g_print("%d %d", this->row_no, this->col_no);
  
  if (Gtk::tmp_char.getChar() == "")  //jeśli w pamięci nie ma żadnej litery
    {
    if ((this->c.getChar() != "") && (this->parent->checkIfModified(this->row_no, this->col_no))) // i jeśli jest litera na polu oraz to pole jest modyfikowalne
	{
	  this->graphic->changeActLetter(this->c.getValue(), this->c.getChar());
	  Gtk::tmp_char = this->c;// to pobierz literę z pola i ją zapamięta
	  this->backToStandart();
	  this->parent->modifyField(this->row_no, this->col_no, false); // a także ustaw pole niezmodyfikowanym
	}
    }
  else // jeśli jest litera w pamięci
    {
      if (this->c.getChar() != "")// i jeśli jest litera na polu
	{
	  if (this->parent->checkIfModified(this->row_no, this->col_no)) // i jeśli to pole jest modyfikowalne
	    {
	      Character exchange;

	      exchange = this->c;
	      this->insert(Gtk::tmp_char);  // to zamień litery
	      Gtk::tmp_char = exchange;
	      this->graphic->changeActLetter(Gtk::tmp_char.getValue(), Gtk::tmp_char.getChar());
	      this->changeButton();
	    }
	}
      else // jeśli nie ma litery na polu
	{

	  this->insert(Gtk::tmp_char);  // to wstaw literę
	  Gtk::tmp_char.backtoStart();
	  this->graphic->changeActLetter(0, (char*)"");
	  this->changeButton();
	  this->parent->modifyField(this->row_no, this->col_no, true);
	}
    }
}

Character Field::getCharacter()
{
  return this->c;
}

void Field::looseBonus()
{
  //
}

void Field::disableButton()
{
  this->graphic->changeSensitivity(this->button, FALSE);
}

void Field::enableButton()
{
  this->graphic->changeSensitivity(this->button, TRUE);
}

Field::~Field()
{
  //
}

void Field::copyData(Field &f)
{
  this->c = f.c;
}
