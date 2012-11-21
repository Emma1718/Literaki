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

  //litery komputera
  for (list<Character>::iterator it=this->letters.begin(); it!=this->letters.end(); ++it)
    cout<<(*it).getChar();
  cout<<endl;

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
/*
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
*/
void Computer::find(int RowOrCol, int nr, string letters, list<int> distances)
{
  int j=0; 
  string letter="";
  letter=letter+letters[j];
  if((int)letters[j]<0) 
    letter=letter+letters[++j];
  ++j;
  int beg=j;
  
  list<int>::iterator it, next;
  set<string>::iterator iter;

  int left, right;
  string word1;

  list<Character> tmp_letters(this->letters.size());
  list<Character>::iterator list_it;

  int begin, end;

  for(iter=dict->words.begin(); iter!=dict->words.end(); ++iter)
    {
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      tmp_letters.clear();
      //copy( this->letters.begin(), this->letters.end(), tmp_letters.begin() );
      // for (list<Character>::iterator list_iter=tmp_letters.begin(); list_iter!=tmp_letters.end(); ++list_iter)
      // {
      //   cout<<"copy:"<<(*list_iter).getChar();
      // }
      // cout<<endl;
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      tmp_letters = copy_list();
      it = distances.begin();
      word1=*iter;
      string cur_letter;

      if(this->contain_letter(word1,letter,left,right) == true) //zawiera pierwsza litere
	{
	  begin=(*it)-left;
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
		  //ok=this->without(tmp_letters,c);
		  list_it=tmp_letters.begin();
		  while( ((*list_it).getChar() != c) && (list_it != tmp_letters.end()) && (!tmp_letters.empty()) )
		    ++list_it;
		  if (list_it != tmp_letters.end())
		    {
		      tmp_letters.erase(list_it);
		      ok=true;
		    }
		  else
		    ok=false;
		  if(!ok) 
		    {
		      //this->without(tmp_letters,"_");
		      list_it=tmp_letters.begin();
		      while( ((*list_it).getChar() != c) && (list_it != tmp_letters.end()) && (!tmp_letters.empty()))
			++list_it;
		      if (list_it != tmp_letters.end())
			{
			  tmp_letters.erase(list_it);
			  ok=true;
			}
		      else
			ok=false;
		    }

		  ++m;
		}
	      if(ok) 
		{

		  ++it;
		  while (right > (*it) && ok)
		    {
		      j=beg;
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
				  //ok=this->without(tmp_letters,c);
				  list_it=tmp_letters.begin();
				  while( ((*list_it).getChar() != c) && (list_it != tmp_letters.end()) && (!tmp_letters.empty()))
				    ++list_it;
				  if (list_it != tmp_letters.end())
				    {
				      tmp_letters.erase(list_it);
				      ok=true;
				    }
				  else
				    ok=false;

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
			  //ok=this->without(tmp_letters,c);
			  list_it=tmp_letters.begin();
			  while( ((*list_it).getChar() != c) && (list_it != tmp_letters.end()) && (!tmp_letters.empty()))
			    ++list_it;
			  if (list_it != tmp_letters.end())
			    {
			      tmp_letters.erase(list_it);
			      ok=true;
			    }
			  else
			    ok=false;
			  ++m;
			}
		      if(ok) 
			{
			  
			  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			  end=begin+(int)word1.length()-1;
			  cout<<*iter<<" begin:"<<begin<<" end:"<<end<<" i:"<<nr<<" "<<RowOrCol<<endl;
			  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		    }
		}
	    }
	}
    }
}

void Computer::findInLine(int RowOrCol, int nr, string &letters, list<int> &distances)
{
  while(letters.length()>0)
    {
      this->find(RowOrCol, nr, letters, distances);

      if((int)letters[0]<0)
	letters=letters.substr(2);
      else
	letters=letters.substr(1);

      distances.pop_front();
    }
  distances.clear();
}


void Computer::findWord()
{
  //tworzymy liste liter i odleglosci pomiedzy nimi
  list<int> distances;
  string letters;

  //dla wszystkich wierszy
  for(int i=0; i<this->map->mapHeight(); ++i)
    {
      this->map->getLine('r',i,letters,distances);
      this->findInLine(1,i,letters,distances);
    }

  //dla wszystkich kolumn
  for(int i=0; i<this->map->mapWidth(); ++i)
    {
      this->map->getLine('c',i,letters, distances);
      this->findInLine(2,i,letters,distances);
    }
  
}


list <Character> Computer::copy_list()
{
  list <Character> tmp_letters;
  
  list<Character>::iterator list_iter;

  //  copy( this->letters.begin(), this->letters.end(), tmp_letters.begin() );


  for (list_iter=this->letters.begin(); list_iter!=this->letters.end(); ++list_iter)
    {
      //      cout<<"letters:"<<(*list_iter).getChar()<<endl;
      tmp_letters.push_back(*list_iter);
    }

  // for (list_iter=tmp_letters.begin(); list_iter!=tmp_letters.end(); ++list_iter)
  //   {
  //     cout<<"copy:"<<(*list_iter).getChar()<<endl;
  //   }
  
  // for (list_iter=this->letters.begin(); list_iter!=this->letters.end(); ++list_iter)
  //   {
  //     cout<<"letters:"<<(*list_iter).getChar();
  //   }

  // cout<<endl;

  return tmp_letters;
}




