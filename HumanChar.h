#ifndef HUMANCHAR_H
#define HUMANCHAR_H

#include "Character.h"
#include "Gtk.h"
//#include "HumanBox.h"

#include <vector>

class HumanChar{

  GtkWidget *button;
  Character letter;
  Gtk * graphic;
  void* parent;
 public:

  bool clicked;
  HumanChar(Character , Gtk *, void *);
  GtkWidget * draw();
  static void ButtonClicked (GtkWidget *, gpointer);  //  ~HumanChar();
  void ButtonClickedEvent(GtkWidget *);
  GtkWidget * getButton();
  Character getLetter();
  void DisableButton();
  void EnableButton();
};


#endif
