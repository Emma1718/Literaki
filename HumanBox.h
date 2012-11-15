#ifndef HUMANBOX_H
#define HUMANBOX_H

#include "HumanChar.h"
#include <list>

class HumanBox{

  HumanChar **lettersBox;
  GtkWidget *board;
  GtkWidget * button_OK;

  Gtk * graphic;
  int length;
 public:
  HumanBox(int, std::list <Character>, Gtk*);
  void draw();
  void loadLetters(std::list <Character> );
  bool Check_if_clicked(Character &);
  void DisableHumanChars();
  void EnableHumanChars();
  void addLetters(std::list <Character>, int);
  // ~HumanBox();
};

#endif
