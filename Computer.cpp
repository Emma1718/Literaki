#include "Computer.h"

using namespace std;

Computer::Computer(string name, int points, Sack * sack, Dictionary *dict, Map * map)
{
  this->name = name;
  this->points = points;
  this->sack = sack;
  this->dict = dict;
  this->map = map;
  this->sack->getCharacters(&(this->letters), 7);
 
  this->findWord("    Ą C      K  ","DSACVZKBF");
  cout<<"skonczylo"<<endl;

}

bool Computer::empty(string line)
{
  for (int i=0; i<(int)line.length(); ++i)
    if (line[i]!=' ')
      return false;
  return true;
}

char Computer::first (string line, int &i)
{
  i=0; 
  string letter="";
  while(line[i]==' ' && i<(int)line.length())
    ++i;
  return line[i];
}

string Computer::letters_and_distances(string line, list<int> &distances)
{
  int i;

  if(empty(line))
    {
      i=(int)line.length();
      distances.push_back(i+1); //ostatnie o 1 wieksze
      return "";
    }
  else
    {
      string letter="";
      letter=letter+first(line,i);

      distances.push_back(i);

      if((int)first(line,i)<0) 
	letter=letter+line[++i];

      line=line.substr(i+1);
      string tmp=letters_and_distances(line,distances);

      return letter+tmp;
    }
}



bool Computer::contain_letter(string word, string letter, int &left, int &right)
{
  string c;
  int i=0,j=0;

  left=0; right=0;

  bool found=false;
  while(!found && i<(int)word.length()) 
    {
      c="";
      c=c+word[i];
      if((int)word[i]<0)
	{
	  ++i;
	  c=c+word[i];
	}
      ++left;

      if(c==letter)
	{
	  found=true;
	  int polish=0;
	  for (int k=++i; k<(int)word.length();++k)
	    if((int)word[k]<0)
	      ++polish;
	  --left;
	  right=(int)word.length()-i-(polish/2);
	}
      ++i;
      ++j;
    }
  if(i==(int)word.length())
    return false;
  else
    return true;
}


string Computer::nth_letter(int n, string word)
{
  int j=0;
  string letter="";
  for(int i=0; i<(int)word.length(); ++i)
    {
      if(j==n)
	{
	  letter=letter+word[i];
	  if((int)word[i]<0)
	    letter=letter+word[i+1];
	}
      if((int)word[i]<0) 
	++i;
      ++j;
    }
  return letter;
}

bool Computer::without(string &word, string letter)
{
  string c, new_string="";
  bool polish_char=false;
  for(int i=0; i<(int)word.length(); ++i)
    {
      c="";
      c=c+word[i];
      if((int)word[i]<0) 
	{
	  c=c+word[++i]; 
	  polish_char=true;
	}
      if(c==letter)
	{
	  if(!polish_char)
	    new_string=word.substr(0,i)+word.substr(i+1);
	  else
	    new_string=word.substr(0,i-1)+word.substr(i+1);
	  word=new_string;
	  return true;
	}
      polish_char=false;
    }
  return false;
}

void Computer::find(string letters, list<int> distances, string comp_letters)
{
  int j=0;
  string letter="";
  letter=letter+letters[j];
  if((int)letters[j]<0) 
    letter=letter+letters[++j];
  ++j;
  int begin=j;

  list<int>::iterator it, next;
  set<string>::iterator iter;

  int left, right;
  string tmp_letters, word1;


  for(iter=dict->words.begin(); iter!=dict->words.end(); ++iter)
    {
      tmp_letters=comp_letters;
      it = distances.begin();
      word1=*iter;
      string cur_letter;

      if(this->contain_letter(word1,letter,left,right) == true) //zawiera pierwsza litere
	{
	  if(left<*it) //wystarczajaco miejsca po lewej
	    {
	      //czy litery po lewej sa w dostepnych literach komputera
	      string c;
	      int m=0;
	      bool ok=true; 
	      while (m<left && ok)
		{
		  c="";
		  c=c+word1[m];
		  if((int)word1[m]<0)
		    c=c+word1[++m];
		  ok=this->without(tmp_letters,c);
		  ++m;
		}
	      if(ok) 
		{

		  ++it;
		  while (right > (*it) && ok)
		    {
		      j=begin;
		      while((right > (*it)) && (it != distances.end()) && ok)
			{
			  cur_letter="";
			  cur_letter=cur_letter+letters[j];
			  if((int)letters[j]<0) 
			    cur_letter=cur_letter+letters[++j];
			  ++j;

			  //sprawdzanie kolejnej litery
			  if(nth_letter(m+1+(*it),word1)==cur_letter)
			    {
			      //sprawdzanie czy litery pomiedzy wpisanymi
			      //sa w literach komputera

			      ++m; //ominiecie znaku juz wpisanego
			      if((int)word1[m]<0)
				++m;

			      int max=m+(*it);
			      while(m<max && ok)
				{
				  c="";
				  c=c+word1[m];
				  if((int)word1[m]<0)
				    c=c+word1[++m];
				  ok=this->without(tmp_letters,c);

				}

			      right=right-(*it);
			      ++it;

			    }
			  else 
			    ok=false;
			}
		    }
		  ok=true;


		  if (right < (*it)) 
		    {
		      //szukanie w comp_letters 
		      ++m; //ominiecie znaku juz wpisanego
		      if((int)word1[m]<0)
			++m;

		      while (m<(int)word1.length() && ok)
			{
			  c="";
			  c=c+word1[m];
			  if((int)word1[m]<0)
			    c=c+word1[++m];
			  ok=this->without(tmp_letters,c);
			  ++m;
			}
		      if(ok) 
			cout<<*iter<<endl;
		    }
		}
	    }
	}
    }
}


void Computer::findWord(string line, string comp_letters)
{
  //tworzymy liste liter i odleglosci pomiedzy nimi
  list<int> distances;
  string letters=this->letters_and_distances(line, distances);
  list<int>::iterator it = distances.begin();
  *it=*it+1; //pierwszy zwiekszony

  while(letters.length()>0)
    {
      this->find(letters, distances, comp_letters);

      if((int)letters[0]<0)
	letters=letters.substr(2);
      else
	letters=letters.substr(1);

      distances.pop_front();
    }
  distances.clear();
}



