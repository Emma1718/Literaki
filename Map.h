#ifndef MAP_H
#define MAP_H

#include "Character.h"
#include "Field.h"
#include "CharBonus.h"
#include "WordBonus.h"
#include "Gtk.h"

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
  void draw ();
  void setField (int x, int y, Character c);
  void putField(int x, int y, GtkWidget *button);
  void clearField (int x, int y);
  void loadFromFile(std::string filename);
  void modify_field(int ,int, bool);
  bool check_if_modified(int, int);
  bool check_move(int &);
  int check_row(int);
  int check_col(int);
  bool check_if_set(int, int);
  void find_words(int );
  int go_left(int , int );
  int go_right(int,int);
  int go_up(int, int);
  int go_down(int, int);

};

#endif 
