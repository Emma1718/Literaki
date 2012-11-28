#include "Computer.h"

using namespace std;

Computer::Computer(string name, int points, Sack * sack, Dictionary *dict, Map * map, string filename)
{
  this->name = name;
  this->points = points;
  this->sack = sack;
  this->dict = dict;
  this->map = map;
  this->sack->getCharacters(&(this->letters), 7);
  this->loadLettersFromFile(filename);
}

Computer::~Computer()
{
  this->letters.clear();
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


bool Computer::find(int RowOrCol, int nr, string letters, list<int> distances, int blanc_amount, clock_t start, bool &tooLong)
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
  int blanc;

  list<Character> tmp_letters(this->letters.size());
  list<Character>::iterator list_it;
     
  int begin;//, end;

  for(iter=dict->words.begin(); iter!=dict->words.end(); ++iter)
    {

      if(((clock()-start)/(double)CLOCKS_PER_SEC) >= maxTime)
	{
	  tooLong=true;
	  return false;
	}

      blanc = blanc_amount;

      tmp_letters.clear();
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
		  while( (list_it != tmp_letters.end()) && ((*list_it).getChar() != c) )
		    {
		      ++list_it;
		    }
		  if (list_it != tmp_letters.end())
		    {
		      tmp_letters.erase(list_it);
		      ok=true;
		    }
		  else
		    {
		      if(blanc>0)
			{
			  --blanc;
			  list_it=tmp_letters.begin();
			  while ( (*list_it).getChar() != "_")
			    ++list_it;
			  tmp_letters.erase(list_it);
			}
		      else
			ok=false;
		    }
		  if(!ok)
		    {
		      //this->without(tmp_letters,"_");
		      list_it=tmp_letters.begin();
		      while( (list_it != tmp_letters.end()) && ((*list_it).getChar() != c) )
			++list_it;
		      if (list_it != tmp_letters.end())
			{
			  tmp_letters.erase(list_it);
			  ok=true;
			}
		      else
			{
			  if(blanc>0)
			    {
			      --blanc;
			      list_it=tmp_letters.begin();
			      while (  (list_it != tmp_letters.end()) && ((*list_it).getChar() != "_") )
				++list_it;
			      tmp_letters.erase(list_it);
			    }
			  else
			    ok=false;
			}
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
				  while(  (list_it != tmp_letters.end()) && ((*list_it).getChar() != c) )
				    ++list_it;
				  if (list_it != tmp_letters.end())
				    {
				      tmp_letters.erase(list_it);
				      ok=true;
				    }
				  else
				    {
				      if(blanc>0)
					{
					  --blanc;
					  list_it=tmp_letters.begin();
					  while ((*list_it).getChar() != "_")
					    ++list_it;
					  tmp_letters.erase(list_it);
					}
				      else
					ok=false;
				    }

				}

			      right=right-(*it);
			      ++it;

			    }
			  else
			    ok=false;
			}
		    }
		  ok=true;


		  if (right < (int)(*it))
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
			  while( ((*list_it).getChar() != c) && (list_it != tmp_letters.end()) )
			    ++list_it;
			  if (list_it != tmp_letters.end())
			    {
			      tmp_letters.erase(list_it);
			      ok=true;
			    }
			  else
			    {
			      if(blanc>0)
				{
				  --blanc;
				  list_it=tmp_letters.begin();
				  while ( ((*list_it).getChar() != "_") && (list_it != tmp_letters.end()) )
				    ++list_it;
				  tmp_letters.erase(list_it);
				}
			      else
				ok=false;
			    }
			  ++m;
			}
		      if(ok)
			{ 
			  tmp_letters.clear();
			  tmp_letters=copy_list();		    
			  list_it=tmp_letters.begin();

			  if(check(word1,tmp_letters,letters, blanc_amount))
			    {
			      if (this->insertWord(*iter, begin, nr, RowOrCol))
				{    
				  bool foundAll = false;
				  list <string> wordsToCheck;
				  list <string>::iterator iter;
				  int cs;
			      
				  if(this->map->checkMove(cs))
				    {
				      list<Character>::iterator itt=tmp_letters.begin();
				 
				      while(itt != tmp_letters.end())				    
					{
					  ++itt;
				      	}
				   
				      this->map->findWords(&wordsToCheck, RowOrCol);
				      for(iter = wordsToCheck.begin(); iter != wordsToCheck.end(); iter++)
					{
					  if(this->dict->checkWord((*iter))==true)
					    foundAll = true;
					  else
					    {
					      foundAll = false;
					      break;
					    }
					}
				      if (foundAll)
					{
					  this->map->drawModFields();
					  this->addPoints(this->map->tmp_sum);
					  return true;
					}
				      else
					{
					  this->map->clearFields();
					  this->map->tmp_sum = 0;
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
  return false;
}

bool Computer::findInLine(int RowOrCol, int nr, string &letters, list<int> &distances, int blanc_amount, clock_t start, bool &tooLong)
{
  
  while(letters.length()>0)
    {
      if(this->find(RowOrCol, nr, letters, distances, blanc_amount, start, tooLong))
	return true;
      else
	if(tooLong)
	  return false;
      
	else
	  letters=letters.substr(1);

      distances.pop_front();
    }
  distances.clear();
  return false;
}

bool Computer::check(string word1, list<Character> tmp_letters, string letters, int blancs_amount)
{
  int j,k=0;
  bool contain;
  bool canInsert=true;
  string c;
  list<Character>::iterator list_it;

  if(letters == word1)
    return false;

  for(int i=0; i<(int)word1.length() && canInsert; ++i)
    {
      c="";
      c=c+word1[i];
      if((int)word1[i]<0)
	c=c+word1[++i];

      j=0;
      contain=false;
      list_it=tmp_letters.begin();

      //czy aktualna litera slowa zawiera sie w literach komputera
      while((!contain) && (list_it != tmp_letters.end()))
	{
	  if((*list_it).getChar() == c)
	    {
	      contain=true;
	      tmp_letters.erase(list_it);
	    }
	  ++list_it;
	  ++j;
	}

      //jezeli nie sprawdzamy, czy jest juz na mapie
      if(!contain)
	{
	  string c1="";
	  while(!contain && k<(int)letters.length())
	    {
	      c1=c1+letters[k];
	      if((int)letters[k]<0)
		c1=c1+letters[++k];

	      if(c == c1)
		contain=true;
	      ++k;
	    }
	}

      if(!contain)
	{
	  if(blancs_amount>0)
	    --blancs_amount;
	  else	
	    return false;
	}	  
    }  
  return true;
}

bool Computer::findWord()
{
  //tworzymy liste liter i odleglosci pomiedzy nimi
  list<int> distances;
  string letters;

  int blanc_amount = 0;
  for(list<Character>::iterator list_it = this->letters.begin(); list_it != this->letters.end(); list_it++)
    if((*list_it).getChar() == "_")
      ++blanc_amount;

  srand(time(NULL));
  int r = rand()%4;

  clock_t start=clock();
  bool tooLong=false;
  
  switch(r)
    {
    case 0:
      //dla wszystkich wierszy   
      for(int i=0; i<this->map->mapHeight(); ++i)
        {
	  this->map->getLine('r',i,letters,distances);
	  if(this->findInLine(1,i,letters,distances, blanc_amount, start, tooLong))
	    return true;    
	  if(tooLong)
	    return false;   
        }
      //dla wszystkich kolumn
      for(int i=0; i<this->map->mapWidth(); ++i)
        {
	  this->map->getLine('c',i,letters, distances);
	  if(this->findInLine(2,i,letters,distances, blanc_amount, start, tooLong))
	    return true;
	  if(tooLong)
	    return false;   
        }
      break;

    case 1:
      //dla wszystkich kolumn
      for(int i=0; i<this->map->mapWidth(); ++i)
        {
	  this->map->getLine('c',i,letters, distances);
	  if(this->findInLine(2,i,letters,distances, blanc_amount, start, tooLong))
	    return true;
	  if(tooLong)
	    return false;   
        }
      //dla wszystkich wierszy   
      for(int i=0; i<this->map->mapHeight(); ++i)
        {
	  this->map->getLine('r',i,letters,distances);
	  if(this->findInLine(1,i,letters,distances, blanc_amount, start, tooLong))
	    return true;       
	  if(tooLong)
	    return false;   
        }
      break;

    case 2:
      //dla wszystkich wierszy   
      for(int i=this->map->mapHeight()-1; i>=0; --i)
        {
	  this->map->getLine('r',i,letters,distances);
	  if(this->findInLine(1,i,letters,distances, blanc_amount, start, tooLong))
	    return true;       
	  if(tooLong)
	    return false;   
        }
      //dla wszystkich kolumn
      for(int i=0; i<this->map->mapWidth(); ++i)
        {
	  this->map->getLine('c',i,letters, distances);
	  if(this->findInLine(2,i,letters,distances, blanc_amount, start, tooLong))
	    return true;
	  if(tooLong)
	    return false;   
        }
      break;

    case 3:
      //dla wszystkich kolumn
      for(int i=0; i<this->map->mapWidth(); ++i)
        {
	  this->map->getLine('c',i,letters, distances);
	  if(this->findInLine(2,i,letters,distances, blanc_amount, start, tooLong))
	    return true;
	  if(tooLong)
	    return false;   
        }
      //dla wszystkich wierszy   
      for(int i=this->map->mapHeight()-1; i>=0; --i)
        {
	  this->map->getLine('r',i,letters,distances);
	  if(this->findInLine(1,i,letters,distances, blanc_amount, start, tooLong))
	    return true;       
        }
      if(tooLong)
	return false;   
      break;
    }
  return false;

}

list <Character> Computer::copy_list()
{
  list <Character> tmp_letters;

  list<Character>::iterator list_iter;

  for (list_iter=this->letters.begin(); list_iter!=this->letters.end(); ++list_iter)
    {
      tmp_letters.push_back(*list_iter);
    }

  return tmp_letters;
}

void Computer::loadLettersFromFile(string filename)
{
  int unimp;
  ifstream read_file(filename.c_str(), ifstream::in);

  while (read_file.good()) //wczytywanie liter i kolorów
    {
      string letter;
      int val;

      read_file>>letter>>unimp>>val;
      this->listOfLetters.push_back(Character(letter, val));
    }

  read_file.close();
}

Character Computer::fromStringToCharacter(string l)
{
  list <Character>::iterator iter;

  for(iter = listOfLetters.begin(); iter != listOfLetters.end(); iter++)
    {
      if(l == (*iter).getChar())
	return (*iter);
    }
}

bool Computer::insertWord(string word, int begin, int nr, int RowOrCol)
{
  string::iterator strIter;
  int i = begin - 1;
  bool ins = false;
  string str = "";
  Character ch;

  for(strIter = word.begin(); strIter < word.end(); strIter++)
    {
      switch(RowOrCol)
	{
	case 1:
	  str = str + (*strIter);
	  if ((int)(*strIter)<0)
	    {
	      strIter++;
	      str = str + (*strIter);
	    }
	  ch = this->fromStringToCharacter(str);
	  if(!ins)
	    ins = this->map->setField(nr,i,ch);
	  else
	    this->map->setField(nr,i,ch);
	  str.clear();
	  break;

	case 2:
	  str = str + (*strIter);
	  if ((int)(*strIter)<0)
	    {
	      strIter++;
	      str = str + (*strIter);
	    }
	  ch = this->fromStringToCharacter(str);
	  if(!ins)
	    ins = this->map->setField(i,nr,ch);
	  else
	    this->map->setField(i,nr,ch);
	  str.clear();
	  break;
	}
      i++;
    }

  return ins;
}

void Computer::addLetters(int amount)
{
  list <Character>::iterator it;

  this->sack->getCharacters(&(this->letters) , amount);
  
  // for(it = this->letters.begin(); it != this->letters.end(); it++)
  //   g_print("After Add:%s\n", (*it).getChar());
}


//tworzy stringa z characters
string Computer::lettersToStr()
{
  string str="";
  list<Character>::iterator list_iter;
  for (list_iter=this->letters.begin(); list_iter!=this->letters.end(); ++list_iter)
    str=str+(*list_iter).getChar();
  return str;
}

//sprawdza (gdy plansza jest pusta) wszystkie mozliwe kombinacje z liter komputera
bool Computer::checkSubset(string subset)
{
  do {
    if(static_cast<Dictionary*> (this->dict)->checkWord(subset)) 
      {
	int begin=1, nr=1, RowOrCol=2;

	int polish=0;
	for(int i=0; i<(int)subset.length(); ++i)
	  if((int)subset[i]<0)
	    ++polish;
	polish=polish/2;

	if((int)subset.length()-polish>=5)
	  {
	    begin=7-(rand()%((int)subset.length()-polish-4))+1;
	    nr=7;
	    RowOrCol=2;
	  }
	else
	  {
	    srand(time(NULL));
	    begin=7-(rand()%((int)subset.length()-polish-1))+1;
	    nr=7;
	    RowOrCol=(rand()%2)+1;		
	  }

	if (this->insertWord(subset, begin, nr, RowOrCol))
	  {      
	    bool foundAll = false;
	    list <string> wordsToCheck;
	    list <string>::iterator iter;
	    int cs;
	    this->map->checkMove(cs);
	    if(this->map->checkMove(cs))
	      {
		this->map->findWords(&wordsToCheck, RowOrCol);
		for(iter = wordsToCheck.begin(); iter != wordsToCheck.end(); iter++)
		  {
		    if(this->dict->checkWord((*iter))==true)
		      foundAll = true;
		    else
		      {
			foundAll = false;
			break;
		      }
		  }
		if (foundAll)
		  {
		    this->map->drawModFields();
		    this->addPoints(this->map->tmp_sum);
		    return true;
		  }
		else
		  {
		    this->map->clearFields();
		    this->map->tmp_sum = 0;
		  }
	      }
	  }
      }
  } while ( next_permutation (subset.begin(),subset.end()) );

  return false;
}

//wywoluje funkcje sprawdzajaca permutacje dla wszystkich podzbiorow
bool Computer::findIfEmpty()
{
  string word=lettersToStr(), tmp=word+word;
  int n=(int)word.length();
  string str;

  for (int k=n; k>1; --k)
    for(int i=0; i<(int)word.length(); ++i)
      if (checkSubset(tmp.substr(i,k)) == true)
	return true;
  return false;
}


