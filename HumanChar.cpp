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
  this->button = graphic->createButton((char*)"", 38 ,38);
  this->drawLetter();
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(HumanChar::buttonClicked), this);
  return this->button;
}

void HumanChar::buttonClicked (GtkWidget * widget, gpointer data)
{
  HumanChar *humanchar = static_cast<HumanChar*>(data);
  humanchar->buttonClickedEvent( humanchar->button);
}


void HumanChar::buttonClickedEvent(GtkWidget * button)
{


  if (Gtk::tmp_char.getChar() == "")
    {
      if  (this->letter.getChar() != "")
	{
	  this->graphic->changeColor(button, 0);
	  this->graphic->setLabel(button, (char*)"");
	  this->graphic->changeActLetter(this->letter.getValue(), this->letter.getChar());
	  Gtk::tmp_char = this->letter;
	  this->letter.backtoStart();
	}
    }
  else
    {
      if (this->letter.getChar() != "")
	{
	  Character exchange;

	  exchange = this->letter;
	  this->letter = Gtk::tmp_char;
	  Gtk::tmp_char = exchange;

	  this->graphic->changeActLetter(Gtk::tmp_char.getValue(), Gtk::tmp_char.getChar());
	  this->graphic->setLabel(this->button, this->letter.getChar());
	  this->graphic->changeColor(this->button, this->letter.getValue());
	}
      else
	{
	  this->letter = Gtk::tmp_char;
	  Gtk::tmp_char.backtoStart();
	  this->graphic->changeActLetter(0, (char*)"");
	  this->graphic->setLabel(this->button, this->letter.getChar());
	  this->graphic->changeColor(this->button, this->letter.getValue());
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

void HumanChar::disableButton()
{
  this->graphic->changeSensitivity(this->button, FALSE);
}

void HumanChar::enableButton()
{
  this->graphic->changeSensitivity(this->button, TRUE);
}

void HumanChar::insert(Character c)
{
  this->letter = c;
}

void HumanChar::clear()
{
  this->letter.backtoStart();
}
void HumanChar::drawLetter()
{
  this->graphic->changeColor(this->button, this->letter.getValue());
  this->graphic->setLabel(this->button, this->letter.getChar());
}

HumanChar::~HumanChar()
{
  delete this->parent;
  delete this->graphic; 
}
