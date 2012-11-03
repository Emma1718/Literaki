#ifndef FIELD_H
#define FIELD_H

#include "Character.h"
#include "Gtk.h"

/// class Field - 
class Field {
  // Associations
  // Attributes
protected:
   Character c;
   GtkWidget *button;
 // Operations
public:
 
  Field ();
  // ~Field ();
  virtual int calculate (int *word_multiplier);
  virtual GtkWidget *draw(Gtk *graphic);
  void insert (Character c);
  //  void Click();
  /* void clear (); */
};

#endif 
