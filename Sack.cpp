#include "Sack.h"

using namespace std;

Sack::Sack(string filename_sack)
{
  ifstream read_file(filename_sack.c_str(), ifstream::in);
  
  int amount, value;
  
  if(read_file.good() ==false)
    {
      string ex = "couldn't open file containing sack!";
      throw ex;
    } 
  
  for(int x=0; 1;)
    {
      string letter;  
      read_file>>letter>>amount>>value;
      if(read_file.good())
	{
	  for(int i=0; i<amount; i++)
	    {
	      Character ch = Character(letter, value);
	      this->characters.insert(pair<int,Character>(x,ch));
	      x++; 
	    }
	}
      else 
	break;
    }
  this->size = this->characters.size();
  read_file.close();
}

int Sack::getCharacters(list <Character> *letters, int amount)
{

  srand(time(NULL));

  int s = this->characters.size();
  int how_many = 0;
  map<int,Character>::iterator iter;
  while(amount>0 && s>0)
    {
      int r = rand()%(this->size);
      iter=this->characters.find(r);
      while(iter == this->characters.end())
	{
	  r = rand()%(this->size);
	  iter = this->characters.find(r);
	}
      letters->push_back((*iter).second);
      if(iter==this->characters.begin())
	{
	  this->characters.erase(iter); 
	  this->characters.begin()= iter++; 
	}
      else
  	{ 
  	  if(iter==this->characters.end())
	    this->characters.erase(iter,this->characters.end());
  	  else 
  	    this->characters.erase(iter);
  	}
      --s;
      --amount;
      ++how_many;
    }
  
  return how_many;
}
				    
Sack::~Sack()
{
  this->characters.clear();
}

Sack::Sack(Sack &s)
{
  map <int, Character>::iterator it;
  for(it = s.characters.begin(); it != s.characters.end(); it++)
    this->characters.insert(*it);
}

void Sack::readSack(Sack &s)
{
  map <int, Character>::iterator it;
  this->characters.clear();

  for(it = s.characters.begin(); it != s.characters.end(); it++)
    this->characters.insert(*it);
}

