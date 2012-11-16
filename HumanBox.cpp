#include "Human.h"

using namespace std;

HumanBox::HumanBox(int l, list <Character> letters, Gtk* graphic)
{
  this->length = l;
  this->loadLetters(letters);
  this->graphic = graphic;
  this->draw();
}

void HumanBox::loadLetters(list <Character> letters)
{
  list <Character>::iterator iter;
 
  this->lettersBox = new HumanChar*[this->length];

  int i;

  for(i=0, iter = letters.begin(); i<this->length, iter != letters.end(); i++, iter++)
    {
      this->lettersBox[i] = new HumanChar(this->graphic, this);
      this->lettersBox[i]->insert(*iter);
    }
}

void HumanBox::draw()
{
  this->board = graphic->Create_Table(this->length,1);
  
  for(int i=0;i<this->length;i++)
    graphic->putField(0,i,this->board,this->lettersBox[i]->draw());
  
  this->button_OK = graphic->Create_Button((char*)"OK", 38, 45);
  g_signal_connect(this->button_OK, "clicked", GTK_SIGNAL_FUNC(Gtk::buttonOKClicked), NULL);
  
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

void HumanBox::addLetters(list <Character> letters, int amount)
{
  int i,j=0;
  list <Character>::reverse_iterator iter;

  for(i = 1, iter = letters.rbegin(); i <= amount, iter != letters.rend(); i++, iter++)
    {
      while(j<this->length)  
	{
	  if (this->lettersBox[j]->getLetter().getChar() == '\0')
	    {
	      cout<<"letterToinsert:"<<(*iter).getChar()<<endl;
	      this->lettersBox[j]->insert(*iter);	
	      this->lettersBox[j]->drawLetter();
	      j++;
	      break;
	    }
	  else j++;
	}
    }
}
