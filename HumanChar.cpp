#include "HumanChar.h"
#include "Human.h"


HumanChar::HumanChar(Character c)
{
  this->letter = c;
  this->clicked = false;
  this->graphic = graphic;
}

GtkWidget *HumanChar::draw()
{
  this->button = graphic->Create_Button((char*)"", 38 ,38);
  switch(this->letter.getValue())
    {
    case 0:
      graphic->ChangeColor(this->button, (char*)"white");
      graphic->setLabel(this->button, (char*)this->letter.getChar());
      break;
    case 1:
      graphic->ChangeColor(this->button, (char*)"yellow");
      graphic->setLabel(this->button, (char*)this->letter.getChar());
      break;
    case 2:
      graphic->ChangeColor(this->button, (char*)"green");
      graphic->setLabel(this->button, (char*)this->letter.getChar());
      break;
    case 3:
      graphic->ChangeColor(this->button,(char*)"royalblue");
      graphic->setLabel(this->button, (char*)this->letter.getChar());
      break;
    case 5:
      graphic->ChangeColor(this->button,(char*)"red");
      graphic->setLabel(this->button, (char*)this->letter.getChar());
      break;
      }
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(HumanChar::ButtonClicked), this);
  return this->button;
}

void HumanChar::ButtonClicked(Gtk * graphic, gpointer data)
{
  HumanChar *humanchar = static_cast<HumanChar*>(data);
  //  humanchar->ButtonClickedEvent(humanchar->button);
  graphic->ChangeColor(humanchar->getButton(), (char*)"white");
  graphic->setLabel(humanchar->getButton(), (char*)"");
  humanchar->clicked = true;
}


void HumanChar::ButtonClickedEvent(GtkWidget * button)
{
  // this->graphic->ChangeColor(button, (char*)"white");
  // this->graphic->setLabel(button, (char*)"");
  // this->clicked = true;
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
  this->graphic->Disable_button(this->button);
}
