#include "Game.h"
using namespace std;

Character Gtk::tmp_char = Character();
Character Gtk::chosenChar = Character();

GtkWidget * Gtk::actual_letter;// = gtk_button_new_with_label((char*)"");
Game *Gtk::game;
GtkWidget *Gtk::chooseWin;

Gtk::Gtk(int argc, char *argv[], Game* parent)
{
  gtk_init(&argc, &argv); //inicjacja biblioteki GTK
  /*Pola*/
  Gtk::game = parent;
  Gtk::actual_letter = this->createButton((char*)"", 38, 38);
  this->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  this->hbox = gtk_hbox_new(FALSE,0);
  this->vbox = gtk_vbox_new(FALSE, 10);


  GtkWidget *frame;
  frame = gtk_frame_new("");
  gtk_widget_set_size_request(frame, 300, 600);
  /*Tworzenie okna*/
  gtk_window_set_title (GTK_WINDOW(this->window), "LiTeRaKi");
  gtk_window_set_position (GTK_WINDOW(this->window), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request(this->window,950,700);
  gtk_window_set_resizable(GTK_WINDOW(this->window), FALSE);

  gtk_container_border_width(GTK_CONTAINER(this->window), 15);
  gtk_container_add(GTK_CONTAINER(this->window), this->hbox);
  gtk_box_pack_start(GTK_BOX(this->hbox), this->vbox, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(this->hbox), frame, TRUE, TRUE, 0);

  g_signal_connect (window, "delete-event", G_CALLBACK (deleteEvent), NULL);
}

GtkWidget * Gtk::createTable(int width, int height)
{
  GtkWidget *board = gtk_table_new(height, width, TRUE);
  return board;
}

GtkWidget * Gtk::createButton(char *label, int height, int width)
{
  GtkWidget *button;

  button = gtk_button_new_with_label(label);
  gtk_widget_set_size_request(button, height, width);

  return button;
}

void Gtk::mapIntoWindow(GtkWidget *board)
{

  gtk_box_pack_start(GTK_BOX(this->vbox), board, TRUE, TRUE, 0);

}
void Gtk::humanboxIntoWindow(GtkWidget *board, GtkWidget *button, GtkWidget *button2)
{
  GtkWidget *hbox;
  hbox = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(this->vbox), hbox, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), board, TRUE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), button2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), Gtk::actual_letter, TRUE, TRUE, 0);
}

void Gtk::changeColor(GtkWidget *widget, int colour_number)
{
  GdkColor color;
  char * colour;
  switch(colour_number)
    {
    case 0:
      colour = (char*)"white";
      break;
    case 1:
      colour = (char*)"yellow";
      break;
    case 2:
      colour = (char*)"green";
      break;
    case 3:
      colour = (char*)"royalblue";
      break;
    case 5:
      colour =(char*)"red";
      break;
    default:
      colour =(char*)"grey";
      break;
    }
  gdk_color_parse(colour, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &color);
  gtk_widget_modify_bg(widget, GTK_STATE_ACTIVE, &color);
}

void Gtk::putField(int x, int y, GtkWidget *board, GtkWidget *button)
{
  gtk_table_attach(GTK_TABLE(board), button, y, y+1, x, x+1, GTK_FILL, GTK_FILL, 0, 0);
}

void Gtk::setLabel(GtkWidget * button, char * c)
{
  gtk_button_set_label(GTK_BUTTON(button), c);
}

void Gtk::run()
{
  gtk_widget_show_all (this->window);
  gtk_main();

}

void Gtk::buttonOKClicked(GtkWidget *widget, gpointer data)
{
  Gtk::game->process();
}

void Gtk::buttonGupClicked(GtkWidget *widget, gpointer data)
{
  Gtk::game->omitMove();
}

void Gtk::changeSensitivity(GtkWidget * button, gboolean x)
{
  gtk_widget_set_sensitive(button, x);
}

void Gtk::changeActLetter(int color, char * letter)
{
  this->changeColor(Gtk::actual_letter, color);
  this->setLabel(Gtk::actual_letter, letter);
}

gboolean Gtk::deleteEvent(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
  gtk_main_quit();
  exit(0); //potem trzeba przerobic na lagodniejsze
}

void Gtk::chooseLetter(string filename)
{
  //GtkWidget * win =
  chooseWin= gtk_window_new(GTK_WINDOW_TOPLEVEL);

  int unimp;

  gtk_window_set_title (GTK_WINDOW(chooseWin), "Wybierz literę");
  gtk_window_set_position (GTK_WINDOW(chooseWin), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request(chooseWin,370,170);
  gtk_window_set_resizable(GTK_WINDOW(chooseWin), FALSE);

  GtkWidget *table = this->createTable(4,8);
  gtk_container_border_width(GTK_CONTAINER(chooseWin), 5);
  gtk_container_add(GTK_CONTAINER(chooseWin), table);

  ifstream file(filename.c_str(), ifstream::in);
 
 
  if (file.is_open())
    {
      for(int i = 0; i < 4; i++)
	for(int j = 0 ; j < 8; j++)
	  {
	    int * val = new int;
	    char * letter = new char[10];
	    file>>letter>>unimp>>*val;
	    GtkWidget * button = this->createButton(letter, 38, 38);
	    this->changeColor(button, *val);
	    this->putField(i, j, table, button);
	    g_signal_connect(button, "clicked", G_CALLBACK(Gtk::letterChosen), (gpointer)val);
	    delete [] letter;
	    //delete val;
	  }
    }

  file.close();
  gtk_widget_show_all(chooseWin);

}

void Gtk::letterChosen(GtkWidget * widget, gpointer data)
{
  char * l;
  l = (char*)gtk_button_get_label(GTK_BUTTON(widget));
  g_print("chosen: %s\n", l);
  int *v;
  v = (int*)data;
  g_print("val:%d\n",*v);
  Character x = Character(l,*v);
  g_print("tmp:%s %d", x.getChar(), x.getValue());
  Gtk::chosenChar = x;
  gtk_widget_destroy(chooseWin);
}

GtkWidget * Gtk::createDialogMessage(const gchar *messageText, GtkDialogFlags flag, GtkButtonsType butType)
{
  GtkWidget *message;

  message=gtk_message_dialog_new(GTK_WINDOW(this->window), flag, GTK_MESSAGE_OTHER, butType, messageText);
  //gtk_widget_set_usize(message,szer,wys);
  gtk_widget_show(message);

  return message;
}

