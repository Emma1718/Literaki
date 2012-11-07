#include "HumanBox.h"

using namespace std;

HumanBox::HumanBox(int l, vector <Character> letters, Gtk* graphic)
{
  this->length = l;
  this->loadLetters(letters);
  this->graphic = graphic;
  this->draw();
}

void HumanBox::loadLetters(vector <Character> letters)
{
  this->lettersBox = new HumanChar*[this->length];

  for(int i=0;i<this->length;i++)
    this->lettersBox[i] = new HumanChar(letters[i]);
}

void HumanBox::draw()
{
  this->board = graphic->Create_Table(this->length,1);
  
  for(int i=0;i<this->length;i++)
    graphic->putField(0,i,this->board,this->lettersBox[i]->draw());
  
  this->button_OK = graphic->Create_Button((char*)"OK", 38, 45);
  graphic->HumanBox_into_window(this->board, this->button_OK);
}

bool HumanBox::Check_if_clicked(Character *c)
{
  int i;
  for (i =0; i < this->length; i++)
    {
      if (this->lettersBox[i]->clicked == true)
	{
	  g_print("Clicked on:%d\n", i);
	  *c = this->lettersBox[i]->getLetter(); 

	  return true;
	}
      else 
	continue;
    }
  return false;
}

void HumanBox::DisableHumanChars()
{
  for(int i = 0; i < this->length; i++)
    {
      if (this->lettersBox[i]->clicked == false)
	{
	  g_print("%s", this->lettersBox[i]->getLetter().getChar());
	  this->lettersBox[i]->DisableButton();
	}
    }
}
      
