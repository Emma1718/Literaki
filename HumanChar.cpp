#include "HumanChar.h"
#include "Human.h"


HumanChar::HumanChar(Character c)
{
  this->letter = c;
}

GtkWidget *HumanChar::draw(Gtk* graphic)
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
  g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(Human::HumanChar_ButtonClicked), this);
  return this->button;
}

// bool HumanChar::ButtonClicked(Character c, Gtk *graphic, gpointer data)
// {
//   HumanChar *humanchar = static_cast<HumanChar*>(data);
//   graphic->ChangeColor(humanchar->button, (char*)"white");
//   c = humanchar->letter;
//   return true;
// }

GtkWidget * HumanChar::getButton()
{
  return this->button;
}

Character HumanChar::getLetter()
{
  return this->letter;
}
