#include "Map.h"

using namespace std;

int Map::tmp_sum = 0;

void Map::loadFromFile(string filename)
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

void Map::draw()
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

void Map::modifyField(int x, int y, bool mod)
{
  this->modified[x][y] = mod;
}

bool Map::checkIfModified(int x, int y)
{
  return (this->modified[x][y]);
}

bool Map::checkMove(int &cs)
{
  int mod_amount = 0, x=-1, y=-1;

  for( int i = 0; i < this->height; i++)
    for( int j = 0; j < this->width; j++)
      {
	if(this->modified[i][j])
	  {
	    cout<<i<<" "<<j<<" "<<this->matrix[i][j]->getCharacter().getChar()<<endl;
	    if (mod_amount==0)
	      {
		x = i;
		y = j;
	      }
	    mod_amount++;
	  }
      }
  if (x<0) return false;
  cs = 0;

  if (this->checkRow(x) != mod_amount)
    {
      if ((this->checkCol(y)) != mod_amount)  return false;
      cs = 2;
    }
  if (cs == 0) cs = 1;

  /*---------Gdy nie zreturnuje to znaczy ze albo w kolumnie albo w wierszu znajduja sie wszystkie zmodyfikowane przyciski */
  g_print("Modifikacje sie zgadzaja \n");

  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this-> width; j++)
      if (this->modified[i][j])
	{
	  if (((i==(this->width/2)) && (i==j)) || this->checkIfSet(i+1, j) || this->checkIfSet(i-1, j) || this->checkIfSet(i, j+1) || this->checkIfSet(i, j-1))
	    {
	      return true;
	    }
	}

  return false;

}

bool Map::checkIfSet(int x, int y)
{

  if((x>=0) && (y>=0) && (x<this->height) && (y<this->width))
    {
      if (!(this->modified[x][y]) && (this->matrix[x][y]->getCharacter().getChar() != '\0'))
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
  	  if (this->matrix[x][j]->getCharacter().getChar() == '\0')
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
  	  if (this->matrix[j][y]->getCharacter().getChar() == '\0')
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

int Map::goLeft(int i, int j)
{
  int a;
  for (a = j; a>=0; a--)
    {
      if(this->matrix[i][a]->getCharacter().getChar() == '\0')
	break;
    }

  return a+1;
}

int Map::goRight(int i, int j)
{
  int a;
  for (a = j; a < this->width; a++)
    {
      if(this->matrix[i][a]->getCharacter().getChar() == '\0')
	break;
    }

  return a-1;
}

int Map::goUp(int i, int j)
{
  int a;
  for (a = i; a>=0; a--)
    {
      if(this->matrix[a][j]->getCharacter().getChar() == '\0')
	break;
    }
  return a+1;
}

int Map::goDown(int i, int j)
{
  int a;
  for (a = i; a<this->height; a++)
    {
      if(this->matrix[a][j]->getCharacter().getChar() == '\0')
	break;
    }
  return a-1;
}

void Map::findWords(list <string> *words, int opt)
{
  bool found1 = false;
  int begin, end;
  string word;// = new char[14];



  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      if(this->modified[i][j])
	{
	  if (!found1)
	    {
	      found1 = true;
	      switch(opt)
		{
		case 1:
		  begin = goLeft(i,j-1);
		  end = goRight(i,j+1);
		  if (begin != end)
		    {
		      for(int p = begin; p<=end; p++)
			{
			  if ((string)this->matrix[i][p]->getCharacter().getChar() != (string)"_")
			    word+=(string)(this->matrix[i][p]->getCharacter().getChar());
			  else
			    {
			      this->graphic->chooseLetter("litery");
			      while (gtk_events_pending())
			      	gtk_main_iteration();
			      sleep(4.5);
			      //while(Gtk::chooseWin);
			    }
			}
		      words->push_back(word);
		      word.clear();
		      this->countPoints(1, begin, end, i);
		    }
		  break;
		case 2:
		  begin = goUp(i-1,j);
		  end = goDown(i+1,j);
		  if (begin != end)
		    {
		      for(int p = begin; p<=end; p++)
			word+=(string)(this->matrix[p][j]->getCharacter().getChar());
		      words->push_back(word);
		      word.clear();
		      this->countPoints(2, begin, end, j);
		    }
		  break;
		}
	      j--;
	    }
	  else
	    {
	      switch(opt)
		{
		case 1:
		  begin = goUp(i-1,j);
		  end = goDown(i+1,j);
		  if (begin != end)
		    {
		      for(int p = begin; p<=end; p++)
			word+=(string)(this->matrix[p][j]->getCharacter().getChar());
		      words->push_back(word);
		      word.clear();
		      this->countPoints(2, begin, end, j);
		    }
		  break;
		case 2:
		  begin = goLeft(i,j-1);
		  end = goRight(i,j+1);
		  if (begin != end)
		    {
		      for(int p = begin; p<=end; p++)
			word+=(string)(this->matrix[i][p]->getCharacter().getChar());
		      words->push_back(word);
		      word.clear();
		      this->countPoints(1, begin, end, i);
		    }
		  break;
		}
	    }
	}
}


void Map::clearModAndBonus()
{
  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      if (this->modified[i][j])
	{
	  this->modified[i][j] = false;
	  this->matrix[i][j]->looseBonus();
	}
}

list <Character> Map::getAllInsertions()
{
  list <Character> insertions;

  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      {
	if (this->modified[i][j])
	  insertions.push_back(this->matrix[i][j]->getCharacter());
      }

  return insertions;
}

void Map::countPoints(int option, int begin, int end, int x)
{
  int word_multiplier = 1;

  switch(option)
    {
    case 1:
      for(int j = begin; j <= end; j++)
	{
	  Map::tmp_sum+= this->matrix[x][j]->calculate(&word_multiplier);
	  cout<<endl<<"word_multiplier:"<<word_multiplier<<endl<<"SUM"<<Map::tmp_sum<<endl;}
      break;

    case 2:
      for(int i = begin; i <= end; i++)
	{
	  Map::tmp_sum+= this->matrix[i][x]->calculate(&word_multiplier);
	}
      break;
    }
  Map::tmp_sum*=word_multiplier;
  cout<<"Sumaopkt:"<<Map::tmp_sum<<endl;
}

void Map::disableMap()
{
  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      this->matrix[i][j]->disableButton();
}

void Map::enableMap()
{
  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this->width; j++)
      this->matrix[i][j]->enableButton();
}

void Map::clearFields()
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
