#include "Map.h"

using namespace std;

int Map::tmp_sum = 0;

void Map::loadFromFile(string filename)  //załaduj mapę z pliku
{

  int option, wh_ch, mp;

  ifstream file(filename.c_str(),ifstream::in);

  if (file.is_open())
    {
      file>>this->height>>this->width;

      this-> matrix=new Field**[this->height];
      for(int i = 0; i<this->height; i++)
	matrix[i]=new Field*[this->width];

      for(int i=0;i<this->height;i++)
        {
          for(int j=0;j<this->width;j++)
            {
              file>>option;
	      switch(option)
		{
		case 0:
		  this->matrix[i][j] = new Field(this, this->graphic, i, j);
		  // g_print("%d %d \n" ,i, j);
		  break;
		case 1:
		  file>>wh_ch>>mp;
		  this->matrix[i][j]=new CharBonus(this, wh_ch, mp, i, j);
		  break;
		case 2:
		  file>>mp;
		  this->matrix[i][j] = new WordBonus(this, mp, i, j);
		  break;
		}
	    }
	}
    }
}

void Map::draw() //narysuj mapę
{
  this->board = graphic->createTable(this->width,this->height);
  for(int i=0; i<this->height; i++)
    for(int j=0; j<this->width; j++)
      {
	graphic->putField(i,j,this->board,this->matrix[i][j]->draw(graphic));
      }
  graphic->mapIntoWindow(this->board);
}

Map::Map(Gtk *graphic,string filename)
{
  this->graphic = graphic;
  this->loadFromFile(filename);
  this->draw();
  /*-----Inicjalizacja masek na macierz--------*/
  this-> modified=new bool*[this->height];

  for(int i = 0; i<this->height; i++)
    modified[i]=new bool[this->width];


  for(int i=0;i<this->height;i++)
    for(int j=0;j<this->width;j++)
      this->modified[i][j] = false;
}

void Map::modifyField(int x, int y, bool mod) //zmodyfikuj pole
{
  this->modified[x][y] = mod;
}

bool Map::checkIfModified(int x, int y) //sprawdz czy jest zmodyfikowane
{
  return (this->modified[x][y]);
}

bool Map::checkMove(int &cs)  //sprawdz ruch, przekaż informację czy zmodyfikowane pla są w rzedzie czy w kolumnie
{
  int mod_amount = 0, x=-1, y=-1;

  for( int i = 0; i < this->height; i++) //zlicz wszsytkie modyfikacje
    for( int j = 0; j < this->width; j++)
      {
	if(this->modified[i][j])
	  {
	    if (mod_amount==0)
	      {
		x = i; //pobierz współrzędne pierwszego zmodyfikowanego
		y = j;
	      }
	    mod_amount++;
	  }
      }
  if (x<0) return false;  //jesli nie ma zmodyfukowanych to niepoprawny ruch
  cs = 0;

  if (this->checkRow(x) != mod_amount)   //jesli w wierszu nie ma wszsytkich zmodyfikowanych pól
    {
      if ((this->checkCol(y)) != mod_amount)  return false; //oraz w kolumnie, niepoprawny ruch
      cs = 2; //jesli jest w kolumnie, przekaz informacje 2
    }
  if (cs == 0) cs = 1;  //jesli jest w wierszu przekaz informacje 1

  /*---------Gdy nie zreturnuje to znaczy ze albo w kolumnie albo w wierszu znajduja sie wszystkie zmodyfikowane przyciski */

  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this-> width; j++)
      if (this->modified[i][j])
	{
	  if (((i==(this->width/2)) && (i==j)) || this->checkIfSet(i+1, j) || this->checkIfSet(i-1, j) || this->checkIfSet(i, j+1) || this->checkIfSet(i, j-1))
	    {
	      return true; // jeśli choć jedno pole ma w otoczeniu ustawione litery bądź znajduje się pośrodku planszy - poprawnych ruch
	    }
	}

  return false; //jeśli wyraz nie graniczy z innym niepoprawny ruch

}

bool Map::checkIfSet(int x, int y) //sprawdz czy dane pole jest ustawione, tzn. czy posiada literę i nie jest modyfikowane
{

  if((x>=0) && (y>=0) && (x<this->height) && (y<this->width))
    {
      if (!(this->modified[x][y]) && (this->matrix[x][y]->getCharacter().getChar() != ""))
	return true;
      else
	return false;
    }
  else return false;
}

int Map::checkRow(int x)
{
  int actual_amount = 0;
  bool interested = false;

  for(int j = 0; j < this->width; j++)
    {
      if (interested)
  	{
  	  if (this->matrix[x][j]->getCharacter().getChar() == "")
  	    break;
  	  else if (this->modified[x][j])
  	    actual_amount++;
  	}
      else if (this->modified[x][j])
	{
	  actual_amount++;
	  interested = true;
	}
    }

  return actual_amount;

}

int Map::checkCol(int y)
{
  int actual_amount = 0;
  bool interested = false;

   for(int j = 0; j < this->height; j++)
    {
      if (interested)
  	{
  	  if (this->matrix[j][y]->getCharacter().getChar() == "")
  	    break;
  	  else if (this->modified[j][y])
  	    actual_amount++;
  	}
      else if (this->modified[j][y])
	{
	  actual_amount++;
	  interested = true;
	}
    }
  return actual_amount;
}

int Map::goLeft(int i, int j) //idz w lewo dopoki nie skonczą się litery lub plansza
{
  int a;
  for (a = j; a>=0; a--)
    {
      if(this->matrix[i][a]->getCharacter().getChar() == "")
	break;
    }

  return a+1;
}

int Map::goRight(int i, int j) //idz w prawo dopoki nie skonczą się litery lub plansza
{
  int a;
  for (a = j; a < this->width; a++)
    {
      if(this->matrix[i][a]->getCharacter().getChar() == "")
	break;
    }

  return a-1;
}

int Map::goUp(int i, int j) //idz do góry dopoki nie skonczą się litery lub plansza
{
  int a;
  for (a = i; a>=0; a--)
    {
      if(this->matrix[a][j]->getCharacter().getChar() == "")
	break;
    }
  return a+1;
}

int Map::goDown(int i, int j) //idz w dół dopoki nie skonczą się litery lub plansza
{
  int a;
  for (a = i; a<this->height; a++)
    {
      if(this->matrix[a][j]->getCharacter().getChar() == "")
	break;
    }
  return a-1;
}

void Map::findWords(list <string> *words, int opt)  //znajdz wyrazy i przekaż je za pomocą listy, pobierz informację czy zmodyfikowane pola są w wierszu czy kolumnie (opt)
{
  bool found1 = false;
  int begin, end;
  string word;// = new char[14];



  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      if(this->modified[i][j]) //dla wszystkich zmodyfikowanych
	{
	  if (!found1) //jesli jest to pierwszy zmodyfikowany
	    {
	      found1 = true;
	      switch(opt)
		{
		case 1: //modyfikacje w wierszu
		  begin = goLeft(i,j-1);
		  end = goRight(i,j+1);
		  if (begin != end) //jesli wyraz jest co najmniej 2lierowy
		    {
		      for(int p = begin; p<=end; p++) //znajdz go
			    word+=this->matrix[i][p]->getCharacter().getChar();
		      words->push_back(word); //wrzuc na listę
		      word.clear();//i wyczyść
		      this->countPoints(1, begin, end, i); //podlicz punkty
		    }
		  break;
		case 2: //modyfikacje w kolumnie
		  begin = goUp(i-1,j);
		  end = goDown(i+1,j);
		  if (begin != end)
		    {
		      for(int p = begin; p<=end; p++)
			word+=this->matrix[p][j]->getCharacter().getChar();
		      words->push_back(word);
		      word.clear();
		      this->countPoints(2, begin, end, j);
		    }
		  break;
		}
	      j--;
	    }
	  else //jesli to juz następne zmodyfikowane pole
	    {
	      switch(opt)
		{
		case 1: //to znajduj kolejne wyrazy w kolumnie
		  begin = goUp(i-1,j);
		  end = goDown(i+1,j);
		  if (begin != end)
		    {
		      for(int p = begin; p<=end; p++)
			word+=this->matrix[p][j]->getCharacter().getChar();
		      words->push_back(word);
		      word.clear();
		      this->countPoints(2, begin, end, j);
		    }
		  break;
		case 2://w wierszu
		  begin = goLeft(i,j-1);
		  end = goRight(i,j+1);
		  if (begin != end)
		    {
		      for(int p = begin; p<=end; p++)
			word+=this->matrix[i][p]->getCharacter().getChar();
		      words->push_back(word);
		      word.clear();
		      this->countPoints(1, begin, end, i);
		    }
		  break;
		}
	    }
	}
}


void Map::clearModAndBonus() //usuń modyfikacje i dostępne bonusy
{
  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      if (this->modified[i][j])
	{
	  this->modified[i][j] = false;
	  this->matrix[i][j]->looseBonus();
	}
}

bool Map::getAllInsertions(bool check, list <Character> &insertions)//pobierz wszystki modyfikacje
{
  //  list <Character> insertions;
  bool isBlank = false;

  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      {
	if (this->modified[i][j])
	  {
	    switch(check)
	      {
	      case false:
		insertions.push_back(this->matrix[i][j]->getCharacter());
		break;
	      case true:
		insertions.push_back(this->matrix[i][j]->getCharacter());
		if(this->matrix[i][j]->getCharacter().getChar() == "_")	  
		  {
		    isBlank = true;
		    this->graphic->chooseLetter("litery", this->matrix[i][j]);
		  }
	      }
	  }
	}
  return isBlank;
}

void Map::countPoints(int option, int begin, int end, int x)
{
  int word_multiplier = 1;//ustaw początkowo mnożnik słowa na 0

  switch(option)
    {
    case 1://jeśli wyraz w wierszu
      for(int j = begin; j <= end; j++)
	Map::tmp_sum+= this->matrix[x][j]->calculate(&word_multiplier);//policz dla każdej komórki, sprawdz czy nie zmienił sie mnożnik słowa
      break;

    case 2://jesli w kolumnie
      for(int i = begin; i <= end; i++)
	Map::tmp_sum+= this->matrix[i][x]->calculate(&word_multiplier);
      break;
    }
  Map::tmp_sum*=word_multiplier;
  cout<<"Sumapkt:"<<Map::tmp_sum<<endl;
}

void Map::disableMap() //dezaktywuj mapę
{
  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      this->matrix[i][j]->disableButton();
}

void Map::enableMap()//aktywuj
{
  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      this->matrix[i][j]->enableButton();
}

void Map::clearFields()//przywróc pola do stanu początkowego
{
  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      if (this->modified[i][j])
	{
	  g_print("clear:%d %d\n", i,j);
         this->matrix[i][j]->backToStandart();
	  this->modified[i][j]=false;
	}
}


bool Map::setField(int x, int y, Character c)
{
  //  this->graphic->setLabel(this->matrix[3][5]->button, "B");
  if (!checkIfSet(x,y))
    {
      this->matrix[x][y]->insert(c);
      this->matrix[x][y]->changeButton();
      cout<<"Wstawiam "<<c.getChar()<<"na "<<x<<" "<<y<<endl;
      return true;
    }
  else return false;
}

void Map::getLine(char RowOrCol, int i, string &letters, list<int> &distances)
{
  letters="";
  int empty=0;

  if(RowOrCol=='r')
    {
      for(int j=0; j<this->width; ++j)
	{
	  if(this->matrix[i][j]->getCharacter().getChar()=="")
	    ++empty;
	  else
	    {
	      distances.push_back(empty);
	      empty=0;
	      letters=letters+this->matrix[i][j]->getCharacter().getChar();
	    }
	}
    }
  else //if(RowOrCol=='c')
    {
      for(int j=0; j<this->height; ++j)
	{
	  if(this->matrix[j][i]->getCharacter().getChar()=="")
	    ++empty;
	  else
	    {
	      distances.push_back(empty);
	      empty=0;
	      letters=letters+this->matrix[j][i]->getCharacter().getChar();
	    }
	}
    }

  distances.push_back(empty);

  list<int>::iterator iter=distances.begin();
  (*iter)=(*iter)+1;

  iter=distances.end(); 
  iter--;
  (*iter)=(*iter)+1;
}

int Map::mapWidth()
{
  return this->width;
}

int Map::mapHeight()
{
  return this->height;
}

Map::~Map()
{
  for(int i = 0; i < this->height; i++)
    delete [] this->modified[i];
  
  delete this->modified;

  for(int i = 0; i < this-> height; i++)
    for(int j = 0; j < this->width; j++)
      delete this->matrix[i][j];

  for(int i = 0; i < this->height; i++)
    delete [] this->matrix[i];
    
   delete this->matrix;


}

