#include "Character.h"

using namespace std;

Character::Character(char * c, int value)
{
  this->c = new char[10];
this->c = c;
  this->value = value;
}

Character::Character()
{
  this->c = '\0';
  this->value = 0;
  }

Character::~Character()
{
  //
}

int Character::getValue()
{
  return this->value;
}

char *Character::getChar()
{
  return this->c;
}

void Character::backtoStart()
{
this->c = '\0';
this->value = 0;
}
