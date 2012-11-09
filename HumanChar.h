#ifndef HUMANCHAR_H
#define HUMANCHAR_H

#include "Character.h"
#include "Gtk.h"


#include <vector>

class HumanBox;

class HumanChar{

  GtkWidget *button;
  Character letter;
  Gtk * graphic;
  HumanBox* parent;
 public:

  bool clicked;
  HumanChar(Character , Gtk *, HumanBox *);
  GtkWidget * draw();
  static void ButtonClicked (GtkWidget *, gpointer);  //  ~HumanChar();
  void ButtonClickedEvent(GtkWidget *);
  GtkWidget * getButton();
  Character getLetter();
  void DisableButton();
  void EnableButton();
};


#endif
