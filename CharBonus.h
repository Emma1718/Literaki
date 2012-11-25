#ifndef CHARBONUS_H
#define CHARBONUS_H

#include "Field.h"

class CharBonus : public Field {

 protected:
  int which_char;
  int multiplier;  // Operations
 public:

  CharBonus(Map *, int, int, int, int);
  CharBonus(CharBonus &);
  ~CharBonus();
  int calculate (int *);
  GtkWidget *draw(Gtk *);
  void looseBonus();
  void backToStandart();
  void changeButton();
  void copyData(Field &);
};

#endif
