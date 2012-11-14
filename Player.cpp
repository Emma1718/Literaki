#include "Player.h"

using namespace std;

bool Player::move()
{
  //
}

void Player::removeLetters(list <Character> insertions)
{
  list <Character>::iterator it, it2;

  for(it2 = insertions.begin(); it2 != insertions.end(); it2++)
    for(it = this->letters.begin(); it != this->letters.end() ;it++)
      {
	if((string)(*it).getChar() == (string)(*it2).getChar())
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


