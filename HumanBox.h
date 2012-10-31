#include "HumanChar.h"

class HumanBox{

  HumanChar **letters;
  GtkWidget *board;
  int length;
 public:
  HumanBox(int l, Gtk *graphic);
  void draw(Gtk *graphic);
  void loadLetters();

  // ~HumanBox();
};
