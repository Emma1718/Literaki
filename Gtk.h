#ifndef GTK_H
#define GTK_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>

class Gtk
{
  GtkWidget *window;
  //  GtkWidget *hpaned;
 public:
  Gtk(int argc, char * argv[]);
  GtkWidget *Create_Table(int width, int height);
  GtkWidget *Create_Button(GtkWidget *board, int col, int row, int id);
  void Table_into_window(GtkWidget *board);
  void run();
  //  ~Gtk();
};

#endif 
