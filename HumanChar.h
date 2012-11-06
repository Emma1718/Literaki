#ifndef HUMANCHAR_H
#define HUMANCHAR_H

#include "Character.h"
#include "Gtk.h"

#include <vector>

class HumanChar{

  GtkWidget *button;
  Character letter;
  Gtk * graphic;
 public:

  bool clicked;
  HumanChar(Character );
  GtkWidget * draw();
  static void ButtonClicked (Gtk *, gpointer);  //  ~HumanChar();
  void ButtonClickedEvent(GtkWidget *);
  GtkWidget * getButton();
  Character getLetter();
  void DisableButton();
};


#endif
