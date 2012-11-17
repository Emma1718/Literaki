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
  static  GtkWidget *chooseWin;
  static Character tmp_char;
  static Character chosenChar;
  static void buttonOKClicked(GtkWidget *widget, gpointer data);
  void changeActLetter(int, char*);

  GtkWidget *createTable(int width, int height);
  GtkWidget *createButton(char *label, int height, int width);
  void changeColor(GtkWidget *,int);
  void mapIntoWindow(GtkWidget *board);
  void humanboxIntoWindow(GtkWidget *, GtkWidget *);
  void putField(int x, int y, GtkWidget *button, GtkWidget *board);
  void setLabel(GtkWidget *, char *);
  void run();
  void changeSensitivity(GtkWidget *, gboolean);
  void chooseLetter(std::string filename);
  static void letterChosen(GtkWidget *, gpointer);
  GtkWidget *createDialogMessage(const gchar *, GtkDialogFlags, GtkButtonsType);

  //  ~Gtk();
};

#endif
