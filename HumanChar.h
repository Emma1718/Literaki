#include "Character.h"
#include "Gtk.h"

class HumanChar{

  GtkWidget *button;
  Character letter;

 public:
  HumanChar();
  GtkWidget * draw(Gtk *graphic);
  void ButtonClicked(Gtk *graphic);  //  ~HumanChar();
};
