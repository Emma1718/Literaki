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
