#include "Player.h"

using namespace std;

void Player::removeLetters(list <Character> insertions)
{
  list <Character>::iterator it, it2;

  for(it2 = insertions.begin(); it2 != insertions.end(); it2++)
    for(it = this->letters.begin(); it != this->letters.end() ;it++)
      {
	if((*it).getChar() == (*it2).getChar())
	  {
	    cout<<"it2:"<<(*it2).getChar()<<"it:"<<(*it).getChar()<<endl;
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
	    break;	
	  }
      }
  for(it = this->letters.begin(); it != this->letters.end() ;it++)
    cout<<"lista:"<<(*it).getChar()<<endl;


}

 void Player::addLetters(int amount)
{
  // list <Character>::iterator it;

  // this->sack->getCharacters(&(this->letters) , amount);
  // for(it = this->letters.begin(); it != this->letters.end(); it++)
  //   cout<<"After Add:"<<(*it).getChar()<<endl;
}

void Player::addPoints(int sum)
{
  this->points+=sum;
  cout<<"ActualPoints:"<<this->points<<endl;
}

int Player::showActPoints()
{
  return this->points;
}

Player::~Player()
{
  //
}
