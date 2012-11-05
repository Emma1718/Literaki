#include "Character.h"
#include "Gtk.h"

#include <vector>

class HumanChar{

  GtkWidget *button;
  Character letter;

 public:
  HumanChar(Character &);
  GtkWidget * draw(Gtk *graphic);
  void ButtonClicked(Gtk *graphic);  //  ~HumanChar();
};
