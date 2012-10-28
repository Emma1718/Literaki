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
  //gtk_widget_show(board);
  return board;
}

GtkWidget * Gtk::Create_Button(GtkWidget *board, int row, int col, int id, int optional)
{
  GtkWidget *button;
  
  button = gtk_button_new();//_with_label("");
  gtk_widget_set_size_request(button, 40, 40);
  gtk_table_attach(GTK_TABLE(board), button, col, col+1, row, row+1, GTK_FILL, GTK_FILL, 0, 0);
  
  if (optional==0)
    {
      switch(id)
	{
	case 0: 
	  this->ChangeColor(button, "white");
	  break;
	case 2:
	  this->ChangeColor(button,"black");
	  break;
	}
    }
  else
    {
      switch(optional)
	{
	case 1:
	  this->ChangeColor(button,"yellow");
	  break;
	case 2:
	  this->ChangeColor(button,"green");
	  break;
	case 3: 
	  this->ChangeColor(button,"blue");
	  break;
	case 5:
	  this->ChangeColor(button,"red");
	  break;
	}
    }
  //  gtk_widget_show(button);
  return button;
}

void Gtk::Table_into_window(GtkWidget *board)
{
  gtk_container_add(GTK_CONTAINER(this->window),board);
}

void Gtk::ChangeColor(GtkWidget *widget, char * colour)
{
  GdkColor color;
  
  gdk_color_parse(colour, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_ACTIVE, &color);
}

void Gtk::run()
{
  gtk_widget_show_all (this->window);
  gtk_main();
}
