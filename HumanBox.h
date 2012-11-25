#ifndef HUMANBOX_H
#define HUMANBOX_H

#include "HumanChar.h"
#include <list>

class HumanBox{

  HumanChar **lettersBox;
  GtkWidget *board;
  GtkWidget * button_OK;
  GtkWidget * giveUpButton;

  Gtk * graphic;
  int length;
 public:
  HumanBox(int, std::list <Character>, Gtk*);
  ~HumanBox();
  void draw();
  void loadLetters(std::list <Character> );
  bool Check_if_clicked(Character &);
  void disableHumanChars();
  void enableHumanChars();
  void addLetters(std::list <Character>, int);
  void drawAfterBack(std::list <Character>);
// ~HumanBox();
};

#endif
