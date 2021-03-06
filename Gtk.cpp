#include "Game.h"

using namespace std;


Character Gtk::tmp_char = Character();
GtkWidget *Gtk::actual_letter;
Game *Gtk::game;
GtkWidget *Gtk::chooseWin;

/*----Mierzenie czasu */
GtkWidget *Gtk::timeLabel1;
int Gtk::seconds;
guint Gtk::clock;
bool Gtk::clockWorking; 


Gtk::Gtk(int argc, char *argv[], Game* parent)
{
  gtk_init(&argc, &argv); //inicjacja biblioteki GTK
  /*Pola*/
  Gtk::game = parent; //wskaznik na gre/rodzica
  Gtk::actual_letter = this->createButton((char*)"", 38, 38); //przycisk z aktualną literą
  /*-----Etykiety z nazwami, czasem i punktami-----*/
  this->nameLabel1 = gtk_label_new("Gracz");
  this->nameLabel2 = gtk_label_new("Komputer");
  this->pointsLabel1 = gtk_label_new("0");
  this->pointsLabel2 = gtk_label_new("0");
  Gtk::timeLabel1 = gtk_label_new("");

  /*---Twprzenie okna głównego i boxów-----*/
  this->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  this->hbox = gtk_hbox_new(FALSE,0);
  this->vbox = gtk_vbox_new(FALSE, 10);
  /*--------------------------------------*/
  /*-----Ramka obok planszy---------*/
  GtkWidget *frame;
  frame = gtk_frame_new("");
  gtk_widget_set_size_request(frame, 300, 600);

  GtkWidget *tableInFrame = this->createTable(6,4);
  GtkWidget *vboxInFrame = gtk_vbox_new(FALSE, 70);
  this->backButton = this->createButton((char*)"Cofnij", 60,100);
  g_signal_connect(this->backButton, "clicked", G_CALLBACK(Gtk::backButtonClicked), NULL);
  
  this->putField(0, 0, tableInFrame, this->nameLabel1);
  this->putField(0, 2, tableInFrame, this->nameLabel2);
  this->putField(2, 0, tableInFrame, this->pointsLabel1);
  this->putField(2, 2, tableInFrame, this->pointsLabel2);
  this->putField(4, 0, tableInFrame, this->timeLabel1);
  
  gtk_box_pack_start(GTK_BOX(vboxInFrame), tableInFrame, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vboxInFrame), this->backButton, FALSE, FALSE, 15);
  gtk_container_border_width(GTK_CONTAINER(frame), 30);
  gtk_container_add(GTK_CONTAINER(frame), vboxInFrame);
  /*---------------------------------------------*/

  /*Tworzenie okna*/
  gtk_window_set_title (GTK_WINDOW(this->window), "LiTeRaKi");
  gtk_window_set_position (GTK_WINDOW(this->window), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request(this->window,950,700);
  gtk_window_set_resizable(GTK_WINDOW(this->window), FALSE);

  gtk_container_border_width(GTK_CONTAINER(this->window), 15);
  gtk_container_add(GTK_CONTAINER(this->window), this->hbox);
  gtk_box_pack_start(GTK_BOX(this->hbox), this->vbox, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(this->hbox), frame, TRUE, TRUE, 0);
  /*sygnał zamnięcia okna*/
  g_signal_connect (window, "delete-event", G_CALLBACK (deleteEvent), NULL);
}

GtkWidget * Gtk::createTable(int width, int height) //tworzy tabele o podanym rozmiarze
 {
  GtkWidget *board = gtk_table_new(height, width, TRUE);
  return board;
}

GtkWidget * Gtk::createButton(char *label, int height, int width) //tworzy przycisk o podanym rozmiarze i etykiecie
{
  GtkWidget *button;

  button = gtk_button_new_with_label(label);
  gtk_widget_set_size_request(button, height, width);

  return button;
}

void Gtk::mapIntoWindow(GtkWidget *board)  //wrzuca planszę do okna
{

  gtk_box_pack_start(GTK_BOX(this->vbox), board, TRUE, TRUE, 0);

}
void Gtk::humanboxIntoWindow(GtkWidget *board, GtkWidget *button, GtkWidget *button2)  //wrzuca wizualizacje liter gracza do okna 
{
  GtkWidget *hbox;
  hbox = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(this->vbox), hbox, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), board, TRUE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), button2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), Gtk::actual_letter, TRUE, TRUE, 0);
}

void Gtk::changeColor(GtkWidget *widget, int colour_number)   //zmienia kolor widżetu (najczęsciej przycisku), zgodnie z podanym numerem
{
  GdkColor color;
  char * colour;
  switch(colour_number)
    {
    case 0:
      colour = (char*)"white";
      break;
    case 1:
      colour = (char*)"#ffff33";
      break;
    case 2:
      colour = (char*)"#99ff99";
      break;
    case 3:
      colour = (char*)"#6699cc";
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

void Gtk::putField(int x, int y, GtkWidget *board, GtkWidget *widget)  //wstawia pole w odpowiedznie miejsce na planszy
{
  gtk_table_attach(GTK_TABLE(board), widget, y, y+1, x, x+1, GTK_FILL, GTK_FILL, 0, 0);
}

void Gtk::setLabel(GtkWidget * button, string c) //ustawia podaną etykietę na przycisku
{
  gtk_button_set_label(GTK_BUTTON(button), (char*)c.c_str());
}

void Gtk::run()  //uruchamia grafikę
{
  gtk_widget_show_all (this->window);
  Gtk::clockWorking = FALSE;
  Gtk::clockStart(); //start zegara
  gtk_main();
}

void Gtk::buttonOKClicked(GtkWidget *widget, gpointer data)  //zdarzenie: kliknięcie na OK
{
  Gtk::game->checkifProcess(); //wywołanie funkcji gry
}

void Gtk::buttonGupClicked(GtkWidget *widget, gpointer data) //zdarzenie: kliknięcie na PAS
{
  Gtk::game->omitMove();
}

void Gtk::backButtonClicked(GtkWidget *, gpointer data)
{
  game->backInHistory();
}

void Gtk::changeSensitivity(GtkWidget * button, gboolean x) //zmiana aktywności widżetu
{
  gtk_widget_set_sensitive(button, x);
}

void Gtk::changeActLetter() //zmiana aktualnie wybranej litery
{
  this->changeColor(Gtk::actual_letter, (Gtk::tmp_char).getValue());
  this->setLabel(Gtk::actual_letter, (Gtk::tmp_char).getChar());
}

void Gtk::changebackButton(int x)
{
  if (x==1) this->changeSensitivity(this->backButton, FALSE);
  if (x>1)  this->changeSensitivity(this->backButton, TRUE);
}

void Gtk::deleteEvent(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
  gtk_main_quit();
}

void Gtk::chooseLetter(string filename, Field *f)  //wyświetlenie okna z literami do wyboru w zamian za blanka, podany plik i wskaznik na pole na którym jest blank
{
  int unimp;

  chooseWin= gtk_window_new(GTK_WINDOW_TOPLEVEL);  
  gtk_window_set_title (GTK_WINDOW(chooseWin), "Wybierz literę");
  gtk_window_set_position (GTK_WINDOW(chooseWin), GTK_WIN_POS_CENTER);
  gtk_widget_set_size_request(chooseWin,370,170);
  gtk_window_set_resizable(GTK_WINDOW(chooseWin), FALSE);
  gtk_window_activate_focus(GTK_WINDOW(chooseWin));


  GtkWidget *table = this->createTable(4,8);
  gtk_container_border_width(GTK_CONTAINER(chooseWin), 5);
  gtk_container_add(GTK_CONTAINER(chooseWin), table);

  ifstream file(filename.c_str(), ifstream::in);


  if (file.is_open()) //wczytywanie liter i kolorów
    {
      for(int i = 0; i < 4; i++)
	for(int j = 0 ; j < 8; j++)
	  {
	    string letter;
	    int val;
	    file>>letter>>unimp>>val;
	    GtkWidget * button = this->createButton((char*)letter.c_str(), 38, 38);
	    this->changeColor(button, val);
	    this->putField(i, j, table, button);
	    g_signal_connect(button, "clicked", G_CALLBACK(Gtk::letterChosen), (gpointer)f);
	  }
    }

  file.close();
  gtk_widget_show_all(chooseWin);
}

void Gtk::letterChosen(GtkWidget * widget, gpointer data)  //funkcja zwrotna kliknięcia/wyboru litery zamiast blanka
 {
  string l;
  l = gtk_button_get_label(GTK_BUTTON(widget));
   
  gtk_widget_hide(chooseWin);  
  
  Character x(l,0);
  Field * field = static_cast<Field*>(data);
  field->insert(x);
  field->changeButton();

  game->process();
}

void Gtk::createDialogMessage(const gchar *messageText)
{
  GtkWidget *message;
  gint result;

  message=gtk_message_dialog_new(GTK_WINDOW(this->window), GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, messageText);
  gtk_widget_set_usize(message,350,150);
  gtk_widget_show(message);

  result = gtk_dialog_run(GTK_DIALOG (message));
  if(result == GTK_RESPONSE_OK)
    gtk_widget_destroy(message);
}

void Gtk::changeActPoints(int which, int actualPoints) //ustawienie odpowiedniej ilości punktów na odpowiedniej etykiecie, 1 - gracz, 2 - komputer
{
  char buffer[10];

  switch(which)
    {
    case 1:
      sprintf(buffer, "%d", actualPoints);
      gtk_label_set(GTK_LABEL(this->pointsLabel1), buffer);
      break;
    case 2:
      sprintf(buffer, "%d", actualPoints);
      gtk_label_set(GTK_LABEL(this->pointsLabel2), buffer);
      break;
    }
}


guint Gtk::clockCallHuman(gpointer data)   //wywoływana co 1sek funkcja zwrotna zegara, zmienia czas na etykiecie gracza
{
  Gtk::seconds--;

  char buffer[10];
  sprintf(buffer, "%d", Gtk::seconds);
  gtk_label_set(GTK_LABEL(Gtk::timeLabel1), buffer);

  if (Gtk::seconds == 0)
    {
      Gtk::clockEnd();
      Gtk::seconds = DEF_SEC;
      Gtk::game->omitMove();
    }
}
void Gtk::clockStart()  //włączenie zegara
{
  if(!Gtk::clockWorking)
    {
      Gtk::seconds = DEF_SEC;
      Gtk::clock = g_timeout_add(1000, GSourceFunc(Gtk::clockCallHuman), NULL);
      Gtk::clockWorking = TRUE;
    }
}

void Gtk::clockEnd()   //zatrzymanie zegara
{
  if(Gtk::clockWorking)
    {
      gtk_timeout_remove(Gtk::clock);
      Gtk::clockWorking = FALSE;
    }
}

