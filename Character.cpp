#include "Character.h"

Character::Character(char c, int value)
{
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

char Character::getChar()
{
  return this->c;
}

