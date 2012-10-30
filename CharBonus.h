#ifndef CHARBONUS_H
#define CHARBONUS_H

#include "Field.h"
                                                                                     
class CharBonus : public Field {

 protected:
  int which_char;
  // Operations                                                                                                                                                         
 public:
 
  CharBonus(int a, int b);
  ~CharBonus();
  int calculate ();
  GtkWidget *draw(Gtk *graphic);
};

#endif 
