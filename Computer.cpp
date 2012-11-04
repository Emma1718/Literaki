#include "Computer.h"

using namespace std;

Computer::Computer(string name, int points, Sack * sack)
{
  vector<Character>::iterator it;
  int i =1;

  this->name = name;
  this->points = points;
  this->sack = sack;

  int x = this->sack->getCharacters(&(this->letters), 7);
  cout<<"Comp:"<<x<<endl;
  for (it=this->letters.begin(); it<this->letters.end(); it++)
    {
      cout <<i<<":"<< (*it).getChar()<<endl;
      i++;
    }

}

