#include "Player.h"

using namespace std;

void Player::removeLetters(list <Character> insertions)
{
  list <Character>::iterator it, it2;
  
  int s = insertions.size();
  int erased = 0;

  for(it2 = insertions.begin(); it2 != insertions.end(); it2++)
    for(it = this->letters.begin(); it != this->letters.end() ;it++)
      {
	if((*it).getChar() == (*it2).getChar())
	  {
	    if(it==this->letters.begin())
	      {
		this->letters.pop_front();
		it=this->letters.begin();
	      }
	    else 
	      {
		this->letters.erase(it);
		it--;
	      }
	    erased++;
	    break;	
	  }
      }

  while(s != erased)  
    {
      for(it = this->letters.begin(); it != this->letters.end() ;it++)
	{
	  if((*it).getChar() == "_")
	    {
	    if(it==this->letters.begin())
	      {
		this->letters.pop_front();
		it=this->letters.begin();
	      }
	    else 
	      {
		this->letters.erase(it);
		it--;
	      }
	    erased++;
	    break;	
	    }
	}
    } 
}

 void Player::addLetters(int amount)
{
  //
}

void Player::addPoints(int sum)
{
  this->points+=sum;
}

int Player::getActPoints()
{
  return this->points;
}

Player::~Player()
{
  //
}

Player::Player()
{
  //
}
Player::Player(Player &copyP)
{
  this->points = copyP.points;

  list <Character>::iterator it;
  for(it = copyP.letters.begin(); it != copyP.letters.end(); it++)
    this->letters.push_back(*it);
}

void Player::readPlayer(Player &pl)
{
  this->points = pl.points;

  this->letters.clear();

  list <Character>::iterator it;
  for(it = pl.letters.begin(); it != pl.letters.end(); it++)
    this->letters.push_back(*it);
}

int Player::getLettersAmount()
{
  return this->letters.size();
}

int Player::getFinalPoints()
{
  list <Character> ::iterator iter;
  int toSubstract = 0;
  int finalP = 0;

  for(iter = this->letters.begin(); iter != this->letters.end(); iter++)
    toSubstract+=(*iter).getValue();
  
  finalP = this->points - toSubstract;

  return finalP;
}

string Player::getName()
{
  return this->name;
}
