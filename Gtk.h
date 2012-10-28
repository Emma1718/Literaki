#ifndef GTK_H
#define GTK_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>


class Gtk
{
  GtkWidget *window;

 public:
  Gtk(int argc, char * argv[]);
  GtkWidget *Create_Table(int width, int height);
  GtkWidget *Create_Button();
  void ChangeColor(GtkWidget *widget,char * colour);
  void Table_into_window(GtkWidget *board);
  void putField(int x, int y, GtkWidget *button, GtkWidget *board);
  void run();
  //  ~Gtk();
};

#endif 
