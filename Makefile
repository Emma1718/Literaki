all:main
main: Character.o CharBonus.o Computer.o Dictionary.o Field.o Game.o Gtk.o HumanBox.o HumanChar.o Human.o main.o Map.o Sack.o WordBonus.o 
	  g++ Character.o CharBonus.o Computer.o Dictionary.o Field.o Game.o Gtk.o HumanBox.o HumanChar.o Human.o main.o Map.o Sack.o WordBonus.o  -o main `pkg-config --cflags --libs gtk+-2.0`
Character.o: Character.cpp Character.h
	    g++ -c Character.cpp -o Character.o
CharBonus.o: CharBonus.cpp CharBonus.h Field.h Character.h Gtk.h
	    g++ -c CharBonus.cpp -o CharBonus.o `pkg-config --cflags --libs gtk+-2.0` 
Computer.o: Computer.cpp Computer.h Player.h Sack.h Character.h
	    g++ -c Computer.cpp -o Computer.o
Dictionary.o: Dictionary.cpp Dictionary.h
	    g++ -c Dictionary.cpp -o Dictionary.o
Field.o: Field.cpp Field.h Character.h Gtk.h
	    g++ -c Field.cpp -o Field.o `pkg-config --cflags --libs gtk+-2.0`
Game.o: Game.cpp Game.h Map.h Character.h Field.h Gtk.h CharBonus.h \
 WordBonus.h Player.h Sack.h Dictionary.h Human.h HumanBox.h HumanChar.h \
 Computer.h
	    g++ -c Game.cpp -o Game.o `pkg-config --cflags --libs gtk+-2.0`
Gtk.o: Gtk.cpp Gtk.h
	    g++ -c Gtk.cpp -o Gtk.o `pkg-config --cflags --libs gtk+-2.0`
HumanBox.o: HumanBox.cpp HumanBox.h HumanChar.h Character.h Gtk.h
	    g++ -c HumanBox.cpp -o HumanBox.o `pkg-config --cflags --libs gtk+-2.0`
 HumanChar.o: HumanChar.cpp HumanChar.h Character.h Gtk.h
	    g++ -c HumanChar.cpp -o HumanChar.o `pkg-config --cflags --libs gtk+-2.0`
Human.o: Human.cpp Human.h Player.h Sack.h Character.h HumanBox.h \
 HumanChar.h Gtk.h
	    g++ -c Human.cpp -o Human.o `pkg-config --cflags --libs gtk+-2.0`
main.o: main.cpp Game.h Map.h Character.h Field.h Gtk.h CharBonus.h \
 WordBonus.h Player.h Sack.h Dictionary.h Human.h HumanBox.h HumanChar.h \
 Computer.h
	    g++ -c main.cpp -o main.o `pkg-config --cflags --libs gtk+-2.0`
Map.o: Map.cpp Map.h Character.h Field.h Gtk.h CharBonus.h WordBonus.h
	    g++ -c Map.cpp -o Map.o `pkg-config --cflags --libs gtk+-2.0`
Sack.o: Sack.cpp Sack.h Character.h
	    g++ -c Sack.cpp -o Sack.o `pkg-config --cflags --libs gtk+-2.0`
WordBonus.o: WordBonus.cpp WordBonus.h Field.h Character.h Gtk.h
	    g++ -c WordBonus.cpp -o WordBonus.o `pkg-config --cflags --libs gtk+-2.0`
clean:
	      rm *.o
	      rm main
