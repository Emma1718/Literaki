#include "Gtk.h"

Gtk::Gtk(int argc, char *argv[])
{
  gtk_init(&argc, &argv);
  this->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW(this->window), "LiTeRaKi");
  gtk_window_set_position (GTK_WINDOW(this->window), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request(this->window,800,600);
  gtk_window_set_resizable(GTK_WINDOW(this->window), FALSE);
  
  this->hpaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_set_border_width(GTK_CONTAINER(this->window),65);

  
  gtk_paned_set_position(GTK_PANED(this->hpaned),500);
 
  gtk_container_add(GTK_CONTAINER(this->window),this->hpaned);
  
}

GtkWidget * Gtk::Create_Table(int width, int height)
{
  GtkWidget *board = gtk_table_new(height, width, TRUE);
  gtk_widget_show(board);
  return board;
}

GtkWidget * Gtk::Create_Button(GtkWidget *board, int col, int row)
{
  GtkWidget *button;
  button = gtk_button_new_with_label("");
  gtk_widget_set_size_request(button, 40, 40);
  gtk_table_attach(GTK_TABLE(board), button, col, col+1, row, row+1, GTK_FILL, GTK_FILL, 0, 0);
  gtk_widget_show(button);
  return button;
}
void Gtk::Table_into_window(GtkWidget *board)
{
  gtk_paned_pack1(GTK_PANED(this->hpaned),board,TRUE,FALSE);
}

void Gtk::run()
{
  gtk_widget_show_all (this->window);
  gtk_main();
}
