#ifndef CHARBONUS_H
#define CHARBONUS_H

#include "Field.h"

/// class TripleBonus -                                                                                                                                                 
class CharBonus : public Field {

  int multiplier;
  int which_char;


  // Operations                                                                                                                                                         
 public:
  CharBonus(int a, int b);
  ~CharBonus();
 void calculate ();
};

#endif 
