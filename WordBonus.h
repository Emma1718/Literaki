#ifndef WORDBONUS_H
#define WORDBONUS_H
#include "Field.h"

/// class TripleBonus -
class WordBonus : public Field {

  // Operations
  int multiplier;
public:
  WordBonus(Map *, int, int, int);
  WordBonus(WordBonus&);
  ~WordBonus();
  int calculate (int *);
  GtkWidget *draw(Gtk *);
  void looseBonus();
  void backToStandart();
  void changeButton();
  void copyData(Field &);
};

#endif
