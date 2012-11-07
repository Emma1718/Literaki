#ifndef GTK_H
#define GTK_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "Character.h"


class Gtk
{
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *hbox;
  bool inserted;


 public:

  static Character tmp_char;

  Gtk(int argc, char * argv[]);
  GtkWidget *Create_Table(int width, int height);
  GtkWidget *Create_Button(char *label, int height, int width);
  void ChangeColor(GtkWidget *,int);
  void Map_into_window(GtkWidget *board);
  void HumanBox_into_window(GtkWidget *, GtkWidget *, GtkWidget *);
  void putField(int x, int y, GtkWidget *button, GtkWidget *board);
  void setLabel(GtkWidget *, char *);
  void run();
  void Change_sensitivity(GtkWidget *, gboolean);
  static  void Click();
  //  ~Gtk();
};

#endif 
