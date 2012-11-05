#include "HumanBox.h"

using namespace std;

HumanBox::HumanBox(int l, Gtk *graphic, vector <Character> letters)
{
  this->length = l;
  this->loadLetters(letters);
  this->draw(graphic);
}

void HumanBox::loadLetters(vector <Character> letters)
{
  this->lettersBox = new HumanChar*[this->length];

  for(int i=0;i<this->length;i++)
    this->lettersBox[i] = new HumanChar(letters[i]);
}

void HumanBox::draw(Gtk *graphic)
{
  this->board = graphic->Create_Table(this->length,1);
  
  for(int i=0;i<this->length;i++)
    graphic->putField(0,i,this->board,this->lettersBox[i]->draw(graphic));
  
  this->button_OK = graphic->Create_Button((char*)"OK", 38, 45);
  graphic->HumanBox_into_window(this->board, this->button_OK);
}
