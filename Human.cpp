#include "Human.h"

using namespace std;

Human::Human(string name, int points, Gtk* graphic, Sack *sack)
{
  vector<Character>::iterator it;
  int i =1;
  this->sack = sack;
  this->name = name;
  this->points = points;
  this->humanbox = new HumanBox(7,graphic);
int x =  this->sack->getCharacters(&(this->letters),7);
 cout<<"Human:"<<x<<endl;
  for (it=letters.begin(); it<letters.end(); it++)
    {
      cout <<i<<":"<< (*it).getChar()<<endl; 
      i++;
    }
}
