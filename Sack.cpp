#include "Sack.h"

using namespace std;

Sack::Sack(string filename_sack)
{
  ifstream read_file(filename_sack.c_str(), ifstream::in);
  char * letter = new char[10];
  int amount, value;

  for(int x=0;1;++x)
    {
      read_file>>letter>>amount>>value;
      if(read_file.good())
	{
	  for(int i=0; i<amount; i++)
	    this->characters.insert(pair<int,Character>(x,Character(letter, value)));
	}
      else 
	break;
    }
  read_file.close();
}

string Sack::getCharacters(int amount)
{
  srand(time(NULL));
  map<int,Character>::iterator iter;
  
  int size=characters.size();
  string buffer="";
  
  while(amount>0 && size>0)
    {
      iter=characters.find(rand()%size);
      //cout<<(*iter).first<<" "<<(*iter).second->c<<" "<<(*iter).second->value<<endl;
      buffer=buffer+(string)(*iter).second.getChar();
      if(iter==characters.begin())
	characters.erase(iter,characters.begin()); 
      else
	{ 
	  if(iter==characters.end())
	    characters.erase(iter,characters.end()); 
	  else 
	    characters.erase(iter);
	}
      --size;
      --amount;
    }
  /*iter=characters.begin();
    while(iter!=characters.end())
    {
    cout<<(*iter).first<<" "<<(*iter).second->c<<" "<<(*iter).second->value<<endl;
    ++iter;
    }*/
  return buffer;
}


				    
