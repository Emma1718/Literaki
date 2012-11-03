#include "Human.h"

using namespace std;

Human::Human(string name, int points, Gtk* graphic, Sack *sack)
{
  this->sack = sack; int i =1;
  this->name = name;
  this->points = points;
  this->humanbox = new HumanBox(7,graphic);
  int x = this->sack->getCharacters(&(this->letters), 99);
  vector<Character>::iterator it;
    for (it=letters.begin(); it<letters.end(); it++)
      {
	cout <<i<<":"<< (*it).getChar()<<endl; 
	i++;
      }
}
