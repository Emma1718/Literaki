#include "Computer.h"

using namespace std;

Computer::Computer(string name, int points, Sack * sack, Dictionary *dict, Map * map)
{
  //vector<Character>::iterator it;
  int i =1;

  this->name = name;
  this->points = points;
  this->sack = sack;
  this->dict = dict;
  this->map = map;
  this->sack->getCharacters(&(this->letters), 7);
  // cout<<"Comp:"<<x<<endl;
  
  // for (i=0; i<this->letters.size(); i++)
  //   cout << " " <<(this->letters[i].getChar())<<endl;
}
  bool Computer::contain_letter(string word, string letter, int &left, int &right)
  {
    string c;
    int i=0;
    bool found=false;
    while(!found && i<(int)word.length()) 
      {
	c="";
	c=c+word[i];
	if(c==letter)
	  {
	    found=true;
	    left=i;
	    right=word.length()-i-1;
	  }
	++i;
      }
    if(i==(int)word.length())
      return false;
    else
      return true;
  }

  bool Computer::without(string &word, string letter)
  {
    string c, new_string="";
    bool contain=false;
    for(int i=0; i<(int)word.length(); ++i)
      {
	c="";
	c=c+word[i];
	if(c!=letter)
	  {
	    new_string=new_string+c;
	    contain=true;
	  }
      }
    word=new_string;
    if(contain)
      return true;
    else
      return false;
  }

  void Computer::findWord(string letters, string letter, int left, int right)
  {
    string word,c,h_sack;
    bool contain;
    int i,l,r;
    set<string>::iterator iter;
    for(iter=dict->words.begin(); iter!=dict->words.end(); ++iter)
      {
	//cout<<*iter<<endl;
	word=*iter;
	i=0;
	h_sack=letters;
	if(this->contain_letter(word,letter,l,r))
	  {
	    if(l<=left && r<=right)
	      {
		contain=true;
		while(i<(int)word.length() && contain)
		  {
		    c="";
		    c=c+word[i];
		    
		    if(!without(h_sack,letter))
		      contain=false;
		  }
		if(contain)
		  cout<<*iter<<endl;
		
	      }
	  }
      }
  }
  


