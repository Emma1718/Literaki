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
   int multiplier;
   GtkWidget *button;
 // Operations
public:
 
  Field ();
  // ~Field ();
  virtual int calculate ();
  virtual GtkWidget *draw(Gtk *graphic);
  //  void insert (Character c);
  /* void clear (); */
};

#endif 
