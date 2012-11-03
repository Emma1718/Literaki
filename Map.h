#ifndef MAP_H
#define MAP_H

#include "Character.h"
#include "Field.h"
#include "CharBonus.h"
#include "WordBonus.h"
#include "Gtk.h"

#include <string>
#include <fstream>

/// class Map - 
class Map {
  // Associations

  // Attributes
 protected:
  bool** modified;
  Field*** matrix;
  GtkWidget *board;
  int height;
  int width;

  // Operations
 public:
  Map (Gtk * graphic,std::string filename);
  //~Map ();
  void draw (Gtk *graphic);
  void setField (int x, int y, Character c);
  void putField(int x, int y, GtkWidget *button);
  void clearField (int x, int y);
  void loadFromFile(std::string filename);
};

#endif 
