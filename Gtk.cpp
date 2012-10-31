#include <iostream>
#include "Gtk.h"

using namespace std;

Gtk::Gtk(int argc, char *argv[])
{
  gtk_init(&argc, &argv); //inicjacja biblioteki GTK

  this->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  this->hbox = gtk_hbox_new(FALSE,0);
  this->vbox = gtk_vbox_new(FALSE, 10);
  /*Tworzenie okna*/ 
  gtk_window_set_title (GTK_WINDOW(this->window), "LiTeRaKi");
  gtk_window_set_position (GTK_WINDOW(this->window), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request(this->window,950,700);
  gtk_window_set_resizable(GTK_WINDOW(this->window), FALSE);

  gtk_container_border_width(GTK_CONTAINER(this->window), 15);
  gtk_container_add(GTK_CONTAINER(this->window), this->hbox);
  gtk_box_pack_start(GTK_BOX(this->hbox), this->vbox, TRUE, TRUE, 5);

}

GtkWidget * Gtk::Create_Table(int width, int height)
{
  GtkWidget *board = gtk_table_new(height, width, TRUE);
  return board;
}

GtkWidget * Gtk::Create_Button()
{
  GtkWidget *button;
  
  button = gtk_button_new();//_with_label("");
  gtk_widget_set_size_request(button, 38, 38);

  return button;
}

void Gtk::Table_into_window(GtkWidget *board)
{
  gtk_box_pack_start(GTK_BOX(this->vbox), board, TRUE, TRUE, 0); 
  /*  GtkWidget *frame;
  frame = gtk_frame_new("STAN GRY");
  gtk_box_pack_start(GTK_BOX(this->hbox), frame, TRUE, TRUE, 0);*/
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
  g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);  
  gtk_main();
  
}

