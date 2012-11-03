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
	      //cout<<x<<"L:"<<ch.getChar()<<endl;
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

int Sack::getCharacters(vector <Character> *letters, int amount)
{
  srand(time(NULL));
  map<int,Character>::iterator iter;
  
  int s = this->characters.size();
  //  cout<<"size:"<<s<<endl;
  int how_many = 0;
//string buffer="";
  
  while(amount>0 && s>0)
    {
      int r = rand()%s;
      cout<<"rand:"<<r<<endl;
      iter=this->characters.find(r);
      while(iter == this->characters.end())
	{
	  r = rand()%s;
	  cout<<"rand2:"<<r<<endl;
	  iter = this->characters.find(r);
	}
      letters->push_back((*iter).second);//cout<<(*iter).first<<" "<<(*iter).second->c<<" "<<(*iter).second->value<<endl;
      //buffer=buffer+(string)(*iter).second.getChar();
      //      cout<<buffer;
      cout<<"iter.char:"<<(*iter).second.getChar()<<endl;
      if(iter==this->characters.begin())
  	this->characters.erase(iter,this->characters.begin()); 
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
  /*iter=characters.begin();
    while(iter!=characters.end())
    {
    cout<<(*iter).first<<" "<<(*iter).second->c<<" "<<(*iter).second->value<<endl;
    ++iter;
    }*/
  return how_many;
}


				    
