#include "HumanChar.h"

class HumanBox{

  HumanChar **lettersBox;
  GtkWidget *board;
  GtkWidget * button_OK;
  int length;
 public:
  HumanBox(int l, Gtk *graphic, std::vector <Character>);
  void draw(Gtk *graphic);
  void loadLetters(std::vector <Character> );

  // ~HumanBox();
};
