#include "HumanBox.h"


HumanChar::HumanChar(Gtk * graphic, HumanBox* hb)
{
  this->letter = Character();
  this->clicked = false;
  this->graphic = graphic;
  this->parent = hb;

}

GtkWidget *HumanChar::draw()
{
  this->button = graphic->Create_Button((char*)"", 38 ,38);
  this->drawLetter();
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(HumanChar::ButtonClicked), this);
  return this->button;
}

void HumanChar::ButtonClicked (GtkWidget * widget, gpointer data)
{
  HumanChar *humanchar = static_cast<HumanChar*>(data);
  humanchar->ButtonClickedEvent( humanchar->button);
}


void HumanChar::ButtonClickedEvent(GtkWidget * button)
{


  if (Gtk::tmp_char.getChar() == '\0')
    {
      if  (this->letter.getChar() != '\0')
	{
	  this->graphic->ChangeColor(button, 0);
	  this->graphic->setLabel(button, (char*)"");
	  //	  this->clicked = true;
	  //this->parent->DisableHumanChars();
	  this->graphic->ChangeActualLetter(this->letter.getValue(), this->letter.getChar());
	  Gtk::tmp_char = this->letter;
	  this->letter.backtoStart();
	}
    }
  else
    {
      if (this->letter.getChar() != '\0')
	{
	  Character exchange;

	  exchange = this->letter;
	  this->letter = Gtk::tmp_char;
	  Gtk::tmp_char = exchange;

	  this->graphic->ChangeActualLetter(Gtk::tmp_char.getValue(), Gtk::tmp_char.getChar());
	  this->graphic->setLabel(this->button, this->letter.getChar());
	  this->graphic->ChangeColor(this->button, this->letter.getValue());
	}
      else
	{
 //this->clicked = false;
	  this->letter = Gtk::tmp_char;
	  Gtk::tmp_char.backtoStart();
	  this->graphic->ChangeActualLetter(0, (char*)"");
	  this->graphic->setLabel(this->button, this->letter.getChar());
	  this->graphic->ChangeColor(this->button, this->letter.getValue());
	  // this->parent->EnableHumanChars();
	}
    }
}

GtkWidget * HumanChar::getButton()
{
  return this->button;
}

Character HumanChar::getLetter()
{
  return this->letter;
}

void HumanChar::DisableButton()
{
  this->graphic->Change_sensitivity(this->button, FALSE);
}

void HumanChar::EnableButton()
{
  this->graphic->Change_sensitivity(this->button, TRUE);
}

void HumanChar::insert(Character c)
{
  this->letter = c;
}

void HumanChar::drawLetter()
{
  this->graphic->ChangeColor(this->button, this->letter.getValue());
  this->graphic->setLabel(this->button, this->letter.getChar());
}
