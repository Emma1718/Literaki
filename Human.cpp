#include "Human.h"
#include <iostream>

using namespace std;

bool  Human::commited = false;

Human::Human(string name, int points, Gtk* graphic, Sack *sack, Map * map)
{
  this->sack = sack;
  this->name = name;
  this->points = points;
  this->sack->getCharacters(&(this->letters),7);
  this->map = map;
  this->humanbox = new HumanBox(7, this->letters, graphic);
}

Human::~Human()
{
  this->letters.clear();
  delete this->humanbox;
}

void Human::addLetters(int amount)
{
  list <Character>::iterator it;

  int i =  this->sack->getCharacters(&(this->letters) , amount);

   this->humanbox->addLetters(this->letters, i);
}

void Human::returnLetters(list <Character> lettersToBack)
{
  this->humanbox->addLetters(lettersToBack, lettersToBack.size());
}

void Human::disableHumanBox()
{
  this->humanbox->disableHumanChars();
}

void Human::enableHumanBox()
{
  this->humanbox->enableHumanChars();
}

void Human::drawAfterBack()
{
  this->humanbox->drawAfterBack(this->letters);
}
