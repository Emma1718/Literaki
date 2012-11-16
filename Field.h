#ifndef FIELD_H
#define FIELD_H

#include "Character.h"
#include "Gtk.h"

class Map;
/// class Field -
class Field {
  // Associations
  // Attributes
protected:
  int row_no;
  int col_no;
  Gtk * graphic;

  GtkWidget *button;
  Map * parent; // Operations
 public:
    Character c;
  Field (Map * , Gtk * , int, int );
  Field ();
  virtual int calculate (int *word_multiplier);
  virtual GtkWidget *draw(Gtk *graphic);
  virtual void backToStandart();
  virtual void looseBonus();
  void insert (Character c);

  static void Click(void *, gpointer);
  void ButtonClickedEvent();
  char * getLetter();
  Character getCharacter();
  void disableButton();
/* static void Enter(void *, gpointer); */
  /* void ButtonEnterEvent();  /\* void clear (); *\/ */
};

#endif
