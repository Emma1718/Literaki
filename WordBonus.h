#ifndef WORDBONUS_H
#define WORDBONUS_H
#include "Field.h"

/// class TripleBonus -
class WordBonus : public Field {

  // Operations
  int multiplier;
public:
  WordBonus(Map *, int, int, int);
  ~WordBonus();
  int calculate (int *);
  GtkWidget *draw(Gtk *);
  void looseBonus();
  void backToStandart();
};

#endif
