#include "HumanChar.h"

class HumanBox{

  HumanChar **letters;
  GtkWidget *board;
  GtkWidget * button_OK;
  int length;
 public:
  HumanBox(int l, Gtk *graphic);
  void draw(Gtk *graphic);
  void loadLetters();

  // ~HumanBox();
};
