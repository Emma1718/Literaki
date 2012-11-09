#include "Human.h"

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
    this->lettersBox[i] = new HumanChar(letters[i], this->graphic, this);
}

void HumanBox::draw()
{
  this->board = graphic->Create_Table(this->length,1);
  
  for(int i=0;i<this->length;i++)
    graphic->putField(0,i,this->board,this->lettersBox[i]->draw());
  
  this->button_OK = graphic->Create_Button((char*)"OK", 38, 45);
  g_signal_connect(this->button_OK, "clicked", GTK_SIGNAL_FUNC(Human::SetCommit), NULL);
  
  graphic->HumanBox_into_window(this->board, this->button_OK);
}


void HumanBox::DisableHumanChars()
{
  for(int i = 0; i < this->length; i++)
    {
      if (this->lettersBox[i]->clicked == false)
  	{
  	  this->lettersBox[i]->DisableButton();
  	}
    }
}
      

void HumanBox::EnableHumanChars()
{
  for(int i = 0; i < this->length; i++)
    {
      this->lettersBox[i]->clicked = false;
      this->lettersBox[i]->EnableButton();
    }
}

