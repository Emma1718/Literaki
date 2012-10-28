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
  // Operations
public:
  GtkWidget *button;
  Field ();
  // ~Field ();
  virtual void calculate ();
  //  void insert (Character c);
  /* void clear (); */
  /* void draw (); */
};

#endif 
