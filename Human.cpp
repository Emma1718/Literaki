#include "Human.h"

using namespace std;

Human::Human(string name, int points, Gtk* graphic, Sack *sack)
{
  //  vector<Character>::iterator it;
  //  int i =1;
  this->sack = sack;
  this->name = name;
  this->points = points;
  this->sack->getCharacters(&(this->letters),7);
  this->humanbox = new HumanBox(7,graphic,(this->letters));
  // for (i=0; i<(int)this->letters.size(); i++)
  //   cout << " " <<(this->letters[i].getChar())<<endl;
  // cout<<"PO:"<<endl;
  // this->sack->getCharacters(&(this->letters),7);
  // this->letters.erase(this->letters.begin()+5);
  // for (i=0; i<(int)this->letters.size(); i++)
  //   cout << " " <<(this->letters[i].getChar())<<endl;
   

}
