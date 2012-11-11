#include "Map.h"

using namespace std;



void Map::loadFromFile(string filename)
{
  
  int option, wh_ch, mp; 

  ifstream file(filename.c_str(),ifstream::in);

  if (file.is_open())
    {
      file>>this->height>>this->width;

      this-> matrix=new Field**[this->width];
      for(int i = 0; i<this->width; i++)
	matrix[i]=new Field*[this->height];

      for(int i=0;i<this->width;i++)
        {
          for(int j=0;j<this->height;j++)
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
  for(int i=0; i<this->width; i++)
    for(int j=0; j<this->height; j++)
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
  this-> modified=new bool*[this->width];

  for(int i = 0; i<this->width; i++)
      modified[i]=new bool[this->height];


  for(int i=0;i<this->width;i++)
    for(int j=0;j<this->height;j++)
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

bool Map::check_move()
{
  int mod_amount = 0, x, y;

  for( int i = 0; i < this->width; i++)
    for( int j = 0; j < this->height; j++)
      {
	if(this->modified[i][j])
	  {
	    cout<<i<<" "<<j<<" "<<this->matrix[i][j]->getLetter()<<endl;
	    if (mod_amount==0)
	      {
		x = i;
		y = j;
	      }
	    mod_amount++;
	  }
      }
  g_print("mod_amount: %d", mod_amount);

  if (this->check_row(y) != mod_amount)
    {
  g_print("Doszedlem tu\n");
      if ((this->check_col(x)) != mod_amount)  return false;
    }
  
  /*---------Gdy nie zreturnuje to znaczy ze albo w kolumnie albo w wierszu znajduja sie wszystkie zmodyfikowane przyciski */

  for(int i = 0; i < this->width; i++)
    for(int j = 0; j < this-> height; j++)
      if (this->modified[i][j])
	{
	  if (((i==(this->width/2)) && (i==j)) || this->check_if_set(x+1, y) || this->check_if_set(x-1, y) || this->check_if_set(x, y+1) || this->check_if_set(x, y-1))
	    return true;
	}
   
  return false;

}

bool Map::check_if_set(int x, int y)
{
  if (!(this->modified[x][y]) && (this->matrix[x][y]->getLetter() != '\0'))
    return true;
  else 
    return false;
}

int Map::check_row(int y)
{
  int actual_amount = 0;
  bool interested = false;

  for(int j = 0; j < this->width; j++)
    {
      if (interested)
  	{
  	  if (this->matrix[j][y]->getLetter() == '\0')
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
  g_print("actual: %d", actual_amount);
  return actual_amount;

}

 int Map::check_col(int x)
{
  int actual_amount = 0;
  bool interested = false;

  for(int j = 0; j < this->width; j++)
    {
      if (interested)
  	{
  	  if (this->matrix[x][j]->getLetter() == '\0')
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
