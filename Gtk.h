#ifndef GTK_H
#define GTK_H

#include <iostream>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "Character.h"


class Game;

class Gtk
{
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *hbox;
  static  GtkWidget *actual_letter;
  static gboolean deleteEvent(GtkWidget *widget, GdkEvent  *event, gpointer data);
  static Game *game;

 public:

  Gtk(int argc, char * argv[], Game *);

  static Character tmp_char;
  static void buttonOKClicked(GtkWidget *widget, gpointer data);
  void ChangeActualLetter(int, char*);

  GtkWidget *Create_Table(int width, int height);
  GtkWidget *Create_Button(char *label, int height, int width);
  void ChangeColor(GtkWidget *,int);
  void Map_into_window(GtkWidget *board);
  void HumanBox_into_window(GtkWidget *, GtkWidget *);
  void putField(int x, int y, GtkWidget *button, GtkWidget *board);
  void setLabel(GtkWidget *, char *);
  void run();
  void Change_sensitivity(GtkWidget *, gboolean);

  //  ~Gtk();
};

#endif 
