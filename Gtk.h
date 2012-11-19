#ifndef GTK_H
#define GTK_H

#include <iostream>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "Character.h"
#include <ctime>

class Game;

class Gtk
{
  GtkWidget *window;

  GtkWidget *vbox;
  GtkWidget *hbox;
  
  static gboolean deleteEvent(GtkWidget *widget, GdkEvent  *event, gpointer data);
  static Game *game;

  static GtkWidget *actual_letter;
  GtkWidget *nameLabel1;
  GtkWidget *nameLabel2;
  GtkWidget *pointsLabel1;
  GtkWidget *pointsLabel2;
  GtkWidget *backButton;  
  static GtkWidget *timeLabel1;
  static GtkWidget *timeLabel2;
  static int seconds;
  static bool clockWorking;
  static guint clock;


 public:

  Gtk(int argc, char * argv[], Game *);
  static GtkWidget *chooseWin;
  static Character tmp_char;
  static Character chosenChar;

  static void buttonOKClicked(GtkWidget *widget, gpointer data);
  static void buttonGupClicked(GtkWidget *widget, gpointer data);
  void changeActLetter(int, std::string);
  void changeActPoints(int, int);

  GtkWidget *createTable(int width, int height);
  GtkWidget *createButton(char *label, int height, int width);
  void changeColor(GtkWidget *,int);
  void mapIntoWindow(GtkWidget *board);
  void humanboxIntoWindow(GtkWidget *, GtkWidget *, GtkWidget *);
  void putField(int x, int y, GtkWidget *button, GtkWidget *board);
  void setLabel(GtkWidget *, std::string);
  void run();
  void changeSensitivity(GtkWidget *, gboolean);
  void chooseLetter(std::string filename);
  static void letterChosen(GtkWidget *, gpointer);
  GtkWidget *createDialogMessage(const gchar *, GtkDialogFlags, GtkButtonsType);
  static void clockStart(int);
  static void clockEnd();
  static guint clockCallHuman(gpointer);
  static guint clockCallComp(gpointer);  //  ~Gtk();
};

#endif
