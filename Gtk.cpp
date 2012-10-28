#include <iostream>
#include "Gtk.h"

using namespace std;

Gtk::Gtk(int argc, char *argv[])
{
  gtk_init(&argc, &argv);
  this->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW(this->window), "LiTeRaKi");
  gtk_window_set_position (GTK_WINDOW(this->window), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request(this->window,800,600);
  gtk_window_set_resizable(GTK_WINDOW(this->window), FALSE);
  
}

GtkWidget * Gtk::Create_Table(int width, int height)
{
  GtkWidget *board = gtk_table_new(height, width, TRUE);
  return board;
}

GtkWidget * Gtk::Create_Button()
{
  GtkWidget *button;
  
  button = gtk_button_new_with_label("");
  gtk_widget_set_size_request(button, 40, 40);

  return button;
}

void Gtk::Table_into_window(GtkWidget *board)
{
  gtk_container_add(GTK_CONTAINER(this->window),board);
}

void Gtk::ChangeColor(GtkWidget *widget, char* colour)
{
  GdkColor color;
  
  gdk_color_parse(colour, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_ACTIVE, &color);
}

void Gtk::putField(int x, int y, GtkWidget *board, GtkWidget *button)
{
  gtk_table_attach(GTK_TABLE(board), button, y, y+1, x, x+1, GTK_FILL, GTK_FILL, 0, 0);
}

void Gtk::run()
{
  gtk_widget_show_all (this->window);
  gtk_main();
}
