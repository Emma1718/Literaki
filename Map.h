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
/// class Map -
class Map {
  // Associations

  // Attributes
  bool** modified;
  Field*** matrix;
  GtkWidget *board;
  int height;
  int width;
  Gtk *graphic;

  // Operations
 public:
  int tmp_sum;

  Map (Gtk * ,std::string);
  ~Map ();
  bool setField (int x, int y, Character c);
  void clearFields ();
  //-----------Rysowanie-------
  void draw ();
  void putField(int x, int y, GtkWidget *button);
  void loadFromFile(std::string filename);
  //-----Klikanie------
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
  //----Usuwanie liter--------
  bool getAllInsertions(bool, std::list <Character> &);

  int mapWidth();
  int mapHeight();
  void getLine(char RowOrCol, int i, std::string &letters, std::list<int> &distances);
};

#endif
