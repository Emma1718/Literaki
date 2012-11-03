#include "Sack.h"

using namespace std;

Sack::Sack(string filename_sack)
{
  ifstream read_file(filename_sack.c_str(), ifstream::in);
  
  int amount, value;

  for(int x=0; 1;)
    {
      char * letter = new char[10];  
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
  // int ss = rand()%s; cout<<"ss="<<ss;
  //iter = characters.find(ss);
  // cout<<"OTO TO:"<<(*iter).first<<" "<<(*iter).second.getChar()<<" "<<(*iter).second.getValue()<<endl;
  read_file.close();
}

string Sack::getCharacters(int amount)
{
  srand(time(NULL));
  map<int,Character>::iterator iter;
  
  int s=characters.size();
  string buffer="";
  
  while(amount>0 && s>0)
    {
      iter=characters.find(rand()%s);
      //cout<<(*iter).first<<" "<<(*iter).second->c<<" "<<(*iter).second->value<<endl;
      buffer=buffer+(string)(*iter).second.getChar();
      //      cout<<buffer;
      if(iter==characters.begin())
  	characters.erase(iter,characters.begin()); 
      else
  	{ 
  	  if(iter==characters.end())
  	    characters.erase(iter,characters.end()); 
  	  else 
  	    characters.erase(iter);
  	}
      --s;
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


				    
