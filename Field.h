#ifndef FIELD_H
#define FIELD_H

#include "Character.h"
#include "Gtk.h"
#include <iostream>

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
  Character c;
  Map * parent; // Operations
 public:

  Field (Map * , Gtk * , int, int );
  Field ();
  Field (const Field &);
  virtual ~Field();

  virtual int calculate (int *word_multiplier);
  virtual GtkWidget *draw(Gtk *graphic);
  virtual void backToStandart();
  virtual void looseBonus();
  virtual void changeButton();
  
  void insert (Character c);
  static void clickButton(void *, gpointer);
  void buttonClickedEvent();
  Character getCharacter();
  void disableButton();
  void enableButton();
  virtual void copyData(Field &);
};

#endif
