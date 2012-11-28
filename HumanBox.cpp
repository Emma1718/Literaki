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

  int i = 0;

  for(iter = letters.begin();iter != letters.end();iter++)
    {
      this->lettersBox[i] = new HumanChar(this->graphic, this);
      this->lettersBox[i]->insert(*iter);
      i++;
    }
}

void HumanBox::draw()
{
  this->board = graphic->createTable(this->length,1);

  for(int i=0;i<this->length;i++)
    graphic->putField(0,i,this->board,this->lettersBox[i]->draw());

  this->button_OK = graphic->createButton((char*)"OK", 38, 45);
  this->giveUpButton = graphic->createButton((char*)"PAS", 38, 45);
  g_signal_connect(this->giveUpButton, "clicked", GTK_SIGNAL_FUNC(Gtk::buttonGupClicked), NULL);
  g_signal_connect(this->button_OK, "clicked", GTK_SIGNAL_FUNC(Gtk::buttonOKClicked), NULL);

  graphic->humanboxIntoWindow(this->board, this->button_OK, this->giveUpButton);
}


void HumanBox::disableHumanChars()
{
  for(int i = 0; i < this->length; i++)
    {
      if (this->lettersBox[i]->clicked == false)
  	{
  	  this->lettersBox[i]->disableButton();
  	}
    }
  this->graphic->changeSensitivity(this->button_OK, FALSE);
  this->graphic->changeSensitivity(this->giveUpButton, FALSE);
}


void HumanBox::enableHumanChars()
{
  for(int i = 0; i < this->length; i++)
    {
      this->lettersBox[i]->clicked = false;
      this->lettersBox[i]->enableButton();
    }
   this->graphic->changeSensitivity(this->button_OK, TRUE);
   this->graphic->changeSensitivity(this->giveUpButton, TRUE);
}

void HumanBox::addLetters(list <Character> letters, int amount)
{
  int i,j=0;
  list <Character>::reverse_iterator iter;
  iter = letters.rbegin();

  for(i = 1; i <= amount; i++)
    {
      while(j<this->length)
	{
	  if (this->lettersBox[j]->getLetter().getChar() == "")
	    {
	      this->lettersBox[j]->insert(*iter);
	      this->lettersBox[j]->drawLetter();
	      j++;
	      iter++;
	      break;
	    }
	  else j++;
	}
    }
}


HumanBox::~HumanBox()
{ 
  for(int i = 0; i < this->length; i++)
    delete this->lettersBox[i];
  delete this->lettersBox;

  delete this->graphic;
}

void HumanBox::drawAfterBack(list <Character> letters)
{
  int i = 0;
  list <Character>::iterator iter;

  for(i = 0; i < this->length; i++)
    this->lettersBox[i]->clear();

  i=0;

  for(iter = letters.begin(); iter != letters.end(); iter++)
    {
      this->lettersBox[i]->insert(*iter);
      this->lettersBox[i]->drawLetter();
      i++;
    }
}
