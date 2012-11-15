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
  this->board = graphic->Create_Table(this->width,this->height);   
  for(int i=0; i<this->height; i++)
    for(int j=0; j<this->width; j++)
      {
	graphic->putField(i,j,this->board,this->matrix[i][j]->draw(graphic));
      }
  graphic->Map_into_window(this->board);
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

void Map::modify_field(int x, int y, bool mod)
{
  this->modified[x][y] = mod;
}
	      
bool Map::check_if_modified(int x, int y)
{
  return (this->modified[x][y]);
}

bool Map::check_move(int &cs)
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

  if (this->check_row(x) != mod_amount)
    {
      if ((this->check_col(y)) != mod_amount)  return false;
      cs = 2;
    }
  if (cs == 0) cs = 1;

  /*---------Gdy nie zreturnuje to znaczy ze albo w kolumnie albo w wierszu znajduja sie wszystkie zmodyfikowane przyciski */

  for(int i = 0; i < this->height; i++)
    for(int j = 0; j < this-> width; j++)
      if (this->modified[i][j])
	{
	  if (((i==(this->width/2)) && (i==j)) || this->check_if_set(x+1, y) || this->check_if_set(x-1, y) || this->check_if_set(x, y+1) || this->check_if_set(x, y-1))
	    {
	      return true;
	    }
	}
   
  return false;

}

bool Map::check_if_set(int x, int y)
{
  if((x>=0) && (y>=0) && (x<this->height) && (y<this->width))
    {
      if (!(this->modified[x][y]) && (this->matrix[x][y]->getCharacter().getChar() != '\0'))
	return true;
      else 
	return false;
    }else return false;
}

int Map::check_row(int x)
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

int Map::check_col(int y)
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

int Map::go_left(int i, int j)
{
  int a;
  for (a = j; a>=0; a--)
    {
      if(this->matrix[i][a]->getCharacter().getChar() == '\0')
	break;
    }
  
  return a+1;
}

int Map::go_right(int i, int j)
{
   int a;
   for (a = j; a < this->width; a++)
    {
      if(this->matrix[i][a]->getCharacter().getChar() == '\0')
	break;
    }
  
  return a-1;
}

int Map::go_up(int i, int j)
{
  int a;
  for (a = i; a>=0; a--)
    {
      if(this->matrix[a][j]->getCharacter().getChar() == '\0')
	break;
    }
  return a+1;
}

int Map::go_down(int i, int j)
{
  int a;
  for (a = i; a<this->height; a++)
    {
      if(this->matrix[a][j]->getCharacter().getChar() == '\0')
	break;
    }
  return a-1;
}

void Map::find_words(list <string> *words, int opt)
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
		  begin = go_left(i,j-1);
		  end = go_right(i,j+1);
		  if (begin != end)
		    {
		      for(int p = begin; p<=end; p++)
			word+=(string)(this->matrix[i][p]->getCharacter().getChar());
		      words->push_back(word);
		      word.clear();
		      this->countPoints(1, begin, end, i);
		    }
		  break;
		case 2:
		  begin = go_up(i-1,j);
		  end = go_down(i+1,j);
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
		  begin = go_up(i-1,j);
		  end = go_down(i+1,j);
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
		  begin = go_left(i,j-1);
		  end = go_right(i,j+1);
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
