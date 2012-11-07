#ifndef HUMANBOX_H
#define HUMANBOX_H

#include "HumanChar.h"


class HumanBox{

  HumanChar **lettersBox;
  GtkWidget *board;
  GtkWidget * button_OK;
  GtkWidget *actual_letter;
  Gtk * graphic;
  int length;
 public:
  HumanBox(int, std::vector <Character>, Gtk*);
  void draw();
  void loadLetters(std::vector <Character> );
  bool Check_if_clicked(Character &);
  void DisableHumanChars();
  void EnableHumanChars();
  void ChangeActualLetter(int, char*);
  // ~HumanBox();
};

#endif
