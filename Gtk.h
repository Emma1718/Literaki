#ifndef GTK_H
#define GTK_H

#include <iostream>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "Character.h"
#include <ctime>

#define DEF_SEC 120  //domyślny czas na ułożenie jednego słowa

class Game;
class Field;

class Gtk
{
  static Game *game; //wskaźnik na grę  
  /*----Głowne widgety----*/ 
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *hbox;
  static GtkWidget *chooseWin;   
  static GtkWidget *actual_letter;
  GtkWidget *nameLabel1;
  GtkWidget *nameLabel2;
  GtkWidget *pointsLabel1;
  GtkWidget *pointsLabel2;
  GtkWidget *backButton;  
  static GtkWidget *timeLabel1;
  static GtkWidget *timeLabel2;
  
  /*----Dla zegara-----*/
  static int seconds;
  static bool clockWorking;
  static guint clock;
  
  static gboolean deleteEvent(GtkWidget *widget, GdkEvent  *event, gpointer data);


public:

  Gtk(int argc, char * argv[], Game *);
  
  static Character tmp_char; //tymczasowa litera, która gracz pobrał z planszy/humanboxa

  /*-----funkcje statyczne, wywoływane na skutek zdarzeń-----*/
  static void buttonOKClicked(GtkWidget *widget, gpointer data);
  static void buttonGupClicked(GtkWidget *widget, gpointer data);
  static void letterChosen(GtkWidget *, gpointer); 
  static guint clockCallHuman(gpointer);
  static guint clockCallComp(gpointer); 


  static void clockStart(int);
  static void clockEnd();

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
  void chooseLetter(std::string filename, Field*);
  GtkWidget *createDialogMessage(const gchar *, GtkDialogFlags, GtkButtonsType);
 //  ~Gtk();

};

#endif
