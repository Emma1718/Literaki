#include "Computer.h"

using namespace std;

Computer::Computer(string name, int points, Sack * sack, Dictionary *dict)
{
  vector<Character>::iterator it;
  int i =1;

  this->name = name;
  this->points = points;
  this->sack = sack;
  this->dict = dict;
  int x = this->sack->getCharacters(&(this->letters), 7);
  // cout<<"Comp:"<<x<<endl;
  
  // for (i=0; i<this->letters.size(); i++)
  //   cout << " " <<(this->letters[i].getChar())<<endl;
  
  
}

