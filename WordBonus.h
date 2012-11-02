#ifndef WORDBONUS_H
#define WORDBONUS_H
#include "Field.h"

/// class TripleBonus - 
class WordBonus : public Field {

  // Operations
  int multiplier;
public:
  WordBonus(int a);
  //  ~WordBonus();
  int calculate ();
  GtkWidget *draw(Gtk *graphic);
};

#endif 
