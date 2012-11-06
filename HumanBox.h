#ifndef HUMANBOX_H
#define HUMANBOX_H

#include "HumanChar.h"

class HumanBox{

  HumanChar **lettersBox;
  GtkWidget *board;
  GtkWidget * button_OK;
  Gtk * graphic;
  int length;
 public:
  HumanBox(int, std::vector <Character>, Gtk*);
  void draw();
  void loadLetters(std::vector <Character> );
  Character Check_if_clicked();
  void DisableHumanChars();
  // ~HumanBox();
};

#endif
