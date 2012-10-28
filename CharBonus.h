#ifndef CHARBONUS_H
#define CHARBONUS_H

#include "Field.h"

/// class TripleBonus -                                                                                                                                                 
class CharBonus : public Field {

 protected:
  int which_char;
  // Operations                                                                                                                                                         
 public:
  //    int which_char;
    CharBonus(int a, int b);
    ~CharBonus();
 void calculate ();
 GtkWidget *draw(Gtk *graphic);
};

#endif 
