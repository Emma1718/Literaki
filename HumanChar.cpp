#include "HumanChar.h"



HumanChar::HumanChar()
{
  //  this->draw(graphic);
}

GtkWidget *HumanChar::draw(Gtk* graphic)
{
  this->button = graphic->Create_Button((char*)"", 38 ,38);
 /* switch(this->letter.getValue())
    {
    case 0:
      graphic->ChangeColor(this->button, "white");
      break;
    case 1:
      graphic->ChangeColor(this->button, "yellow");
      break;
    case 2:
      graphic->ChangeColor(this->button, "green");
      break;
    case 3:
      graphic->ChangeColor(this->button,"blue");
      break;
    case 5:
      graphic->ChangeColor(this->button,"red");
      break;
      }*/
 // g_signal_connect(this->button, "clicked", GTK_SIGNAL_FUNC(ButtonClicked), graphic);
  return this->button;
}

void HumanChar::ButtonClicked(Gtk *graphic)
{
  //  graphic->ChangeColor(this->button, "deeppink");
}
