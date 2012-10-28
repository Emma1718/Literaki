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
  Field*** matrix;
  // Attributes
protected:
  bool** modified;
  // Operations
public:
  GtkWidget *board;
  int height;
  int width;
  Map (Gtk * graphic);
  //~Map ();
  void draw (Gtk *graphic);
  void setField (int x, int y, Character c);
  void clearField (int x, int y);
  void loadFromFile(std::string filename);
};

#endif 
