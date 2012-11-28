#ifndef MAP_H
#define MAP_H

#include "Character.h"
#include "Field.h"
#include "CharBonus.h"
#include "WordBonus.h"
#include "Gtk.h"

#include <list>
#include <string>
#include <fstream>
#include <iostream>

class Map {

  bool** modified;
  Field*** matrix;
  int ** helpMat;
 
  GtkWidget *board;
  Gtk *graphic;  
  
  int height;
  int width;
  
 public:
  int tmp_sum;

  Map (Gtk * ,std::string);
  Map(const Map &);
  ~Map ();
  
  void loadFromFile(std::string filename);
  void draw ();
  
  bool setField (int x, int y, Character c);
  void clearFields ();
  void drawModFields();

  void modifyField(int ,int, bool);
  bool checkIfModified(int, int);
  //----Sprawdzanie ruchu----
  bool checkMove(int &);
  int checkRow(int);
  int checkCol(int);
  bool checkIfSet(int, int);
  //-----Sprawdzanie słów-------
  void findWords(std::list <std::string> *, int );
  int goLeft(int , int );
  int goRight(int,int);
  int goUp(int, int);
  int goDown(int, int);
  void clearModAndBonus();
  void countPoints(int, int, int, int);
  void disableMap();
  void enableMap();

  bool getAllInsertions(bool, std::list <Character> &);

  int mapWidth();
  int mapHeight();
  void getLine(char RowOrCol, int i, std::string &letters, std::list<int> &distances);
  bool isEmpty();

  void readMap(Map &);
  void drawAfterBack();

};

#endif
