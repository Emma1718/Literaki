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
  Map (Gtk * ,std::string);
  //~Map ();
  void setField (int x, int y, Character c);
  void clearField (int x, int y);
  //-----------Rysowanie-------
  void draw ();
  void putField(int x, int y, GtkWidget *button);
  void loadFromFile(std::string filename);
  //-----Klikanie------
  void modify_field(int ,int, bool);
  bool check_if_modified(int, int);
  //----Sprawdzanie ruchu----
  bool check_move(int &);
  int check_row(int);
  int check_col(int);
  bool check_if_set(int, int);
  //-----Sprawdzanie słów-------
  void find_words(std::list <std::string> *, int );
  int go_left(int , int );
  int go_right(int,int);
  int go_up(int, int);
  int go_down(int, int);
  void clearModifications();
  //----Usuwanie liter--------
  std::list <Character> getAllInsertions();
};

#endif 
