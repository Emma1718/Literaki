#ifndef FIELD_H
#define FIELD_H

#include "Character.h"
#include "Gtk.h"


/// class Field - 
class Field {
  // Associations
  // Attributes
protected:
  int row_no;
  int col_no;
  Gtk * graphic;
  Character c;
  GtkWidget *button;
  void * parent; // Operations
 public:
  
  Field (void * , Gtk * , int, int );
  Field ();
  virtual int calculate (int *word_multiplier);
  virtual GtkWidget *draw(Gtk *graphic);
  void insert (Character c);
  static void Click(void *, gpointer);
  void ButtonClickedEvent();
  /* static void Enter(void *, gpointer); */
  /* void ButtonEnterEvent();  /\* void clear (); *\/ */
};

#endif 
