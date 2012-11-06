#ifndef GTK_H
#define GTK_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>


class Gtk
{
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *hbox;
  bool inserted;
 public:
  Gtk(int argc, char * argv[]);
  GtkWidget *Create_Table(int width, int height);
  GtkWidget *Create_Button(char *label, int height, int width);
  void ChangeColor(GtkWidget *widget,char * colour);
  void Map_into_window(GtkWidget *board);
  void HumanBox_into_window(GtkWidget *board, GtkWidget *button);
  void putField(int x, int y, GtkWidget *button, GtkWidget *board);
  void setLabel(GtkWidget *, char *);
  void run();
  void Disable_button(GtkWidget *);
  static  void Click();
  //  ~Gtk();
};

#endif 
