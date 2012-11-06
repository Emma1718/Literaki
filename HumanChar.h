#ifndef HUMANCHAR_H
#define HUMANCHAR_H

#include "Character.h"
#include "Gtk.h"

#include <vector>

class HumanChar{

  GtkWidget *button;
  Character letter;

 public:
  HumanChar(Character );
  GtkWidget * draw(Gtk *graphic);
  //  static bool ButtonClicked(Character, Gtk *, gpointer);  //  ~HumanChar();
  GtkWidget * getButton();
  Character getLetter();
};


#endif
