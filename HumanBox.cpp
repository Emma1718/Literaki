#include "HumanBox.h"

using namespace std;

HumanBox::HumanBox(int l, Gtk *graphic)
{
  this->length = l;
  this->loadLetters();
  this->draw(graphic);
}

void HumanBox::loadLetters()
{
  this->letters = new HumanChar*[this->length];

  for(int i=0;i<this->length;i++)
    this->letters[i] = new HumanChar();
}

void HumanBox::draw(Gtk *graphic)
{
  this->board = graphic->Create_Table(this->length,1);
  
  for(int i=0;i<this->length;i++)
    graphic->putField(0,i,this->board,this->letters[i]->draw(graphic));
  this->button_OK = graphic->Create_Button((char*)"OK", 38, 45);

  graphic->HumanBox_into_window(this->board, this->button_OK);
}
