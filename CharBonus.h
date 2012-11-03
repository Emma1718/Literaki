#ifndef CHARBONUS_H
#define CHARBONUS_H

#include "Field.h"
                                                                                     
class CharBonus : public Field {

 protected:
  int which_char;
  int multiplier;  // Operations                                                                                                                                                         
 public:
 
  CharBonus(int a, int b);
  ~CharBonus();
  int calculate (int * word_multiplier);
  GtkWidget *draw(Gtk *graphic);
};

#endif 
