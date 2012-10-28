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
  //GdkColor color;
  //gdk_color_parse("blue", &color);
  //gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);  
  //  this->hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  // gtk_container_set_border_width(GTK_CONTAINER(this->window),65);

  
  //gtk_paned_set_position(GTK_PANED(this->hpaned),500);
 
  //  gtk_container_add(GTK_CONTAINER(this->window),this->hpaned);
  
}

GtkWidget * Gtk::Create_Table(int width, int height)
{
  GtkWidget *board = gtk_table_new(height, width, TRUE);
  //gtk_widget_show(board);
  return board;
}

GtkWidget * Gtk::Create_Button(GtkWidget *board, int row, int col, int id)
{
  GtkWidget *button;
  GdkColor color;
  button = gtk_button_new();//_with_label("");
  gtk_widget_set_size_request(button, 40, 40);
  gtk_table_attach(GTK_TABLE(board), button, col, col+1, row, row+1, GTK_FILL, GTK_FILL, 0, 0);
  
  switch(id)
    {
    case 0: 
     GdkRGBA kolor;
         gdk_rgba_parse (&kolor, "red");
     gtk_widget_override_color(button,GTK_STATE_FLAG_PRELIGHT, &kolor);      
     // gdk_color_parse("red",&color);
     //     gtk_widget_modify_bg(button, GTK_STATE_NORMAL,&color);
     //gtk_widget_modify_bg(button, GTK_STATE_PRELIGHT,&color);
     //gtk_widget_modify_bg(button, GTK_STATE_ACTIVE,&color);
	    //            gtk_widget_override_background_color(button, GTK_STATE_FLAG_NORMAL, 0.5);
      break;
      /* case 1:
      gdk_color_parse("red", &color);
      gtk_widget_modify_bg(button,GTK_STATE_NORMAL,&color);
      break;
    case 2:
      gdk_color_parse("black", &color);
      gtk_widget_modify_bg(button,GTK_STATE_NORMAL,&color);
      break;
      */    }

  //  gtk_widget_show(button);
  return button;
}
void Gtk::Table_into_window(GtkWidget *board)
{
  gtk_container_add(GTK_CONTAINER(this->window),board);
}

void Gtk::run()
{
  gtk_widget_show_all (this->window);
  gtk_main();
}
