all:main
main: Game.o  Dictionary.h main.o  Dictionary.h 
	  g++ Game.o  Dictionary.h main.o  Dictionary.h  -o main
Game.o: Game.cpp Game.h Sack.h Gtk.h Map.h Character.h Field.h Player.h \
 Dictionary.h
	    g++ -c Game.cpp -o Game.o
main.o: main.cpp Game.h Sack.h Gtk.h Map.h Character.h Field.h Player.h \
 Dictionary.h
	    g++ -c main.cpp -o main.o
clean:
	      rm *.o
	      rm main
