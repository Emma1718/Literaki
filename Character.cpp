#include "Character.h"

using namespace std;

Character::Character(string c, int value)
{
  this->c = c;
  this->value = value;
}

Character::Character()
{
  this->c = "";
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

string Character::getChar()
{
  return this->c;
}

void Character::backtoStart()
{
this->c = "";
this->value = 0;
}
