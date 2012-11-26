#ifndef WORDBONUS_H
#define WORDBONUS_H
#include "Field.h"

class WordBonus : public Field {

  int multiplier;

public:

  WordBonus(Map *, int, int, int);
  WordBonus(const WordBonus&);
  ~WordBonus();

  GtkWidget *draw(Gtk *);
  int calculate (int *);
  void looseBonus();
  void backToStandart();
  void changeButton();
  void copyData(Field &);
};

#endif
