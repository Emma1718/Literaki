
#include "Human.h"
#include <iostream>

using namespace std;

bool  Human::commited = false;

Human::Human(string name, int points, Gtk* graphic, Sack *sack, Map * map)
{
  //  vector<Character>::iterator it;
  //  int i =1;
  this->sack = sack;
  this->name = name;
  this->points = points;
  this->sack->getCharacters(&(this->letters),7);
  this->map = map;
  this->humanbox = new HumanBox(7,(this->letters), graphic);
  // for (i=0; i<(int)this->letters.size(); i++)
  //   cout << " " <<(this->letters[i].getChar())<<endl;
  // cout<<"PO:"<<endl;
  // this->sack->getCharacters(&(this->letters),7);
  // this->letters.erase(this->letters.begin()+5);
  // for (i=0; i<(int)this->letters.size(); i++)
  //   cout << " " <<(this->letters[i].getChar())<<endl;
   

}

void Human::SetCommit()
{
  Human::commited = true;
}

bool Human::move()
{
  while(Human::commited == false); 
  return true;
}
