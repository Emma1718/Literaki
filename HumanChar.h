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
  HumanChar(Gtk *, HumanBox *);
  GtkWidget * draw();
  static void buttonClicked (GtkWidget *, gpointer);  //  ~HumanChar();
  void buttonClickedEvent(GtkWidget *);
  GtkWidget * getButton();
  Character getLetter();
  void insert(Character c);
  void drawLetter();
  void disableButton();
  void enableButton();
};


#endif
