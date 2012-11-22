all:main
main: Character.o CharBonus.o Computer.o Dictionary.o Field.o Game.o Gtk.o History.o HumanBox.o HumanChar.o Human.o main.o Map.o Player.o Sack.o WordBonus.o 
	  g++ Character.o CharBonus.o Computer.o Dictionary.o Field.o Game.o Gtk.o History.o HumanBox.o HumanChar.o Human.o main.o Map.o Player.o Sack.o WordBonus.o  -o main `pkg-config --cflags --libs gtk+-2.0`
Character.o: Character.cpp Character.h
	    g++ -Wall -c Character.cpp -o Character.o `pkg-config --cflags --libs gtk+-2.0`
CharBonus.o: CharBonus.cpp CharBonus.h Field.h Character.h Gtk.h
	    g++ -Wall -c CharBonus.cpp -o CharBonus.o `pkg-config --cflags --libs gtk+-2.0`
Computer.o: Computer.cpp Computer.h Player.h Sack.h Character.h Map.h \
 Field.h Gtk.h CharBonus.h WordBonus.h Dictionary.h
	    g++ -Wall -c Computer.cpp -o Computer.o `pkg-config --cflags --libs gtk+-2.0`
Dictionary.o: Dictionary.cpp Dictionary.h
	    g++ -Wall -c Dictionary.cpp -o Dictionary.o `pkg-config --cflags --libs gtk+-2.0`
Field.o: Field.cpp Map.h Character.h Field.h Gtk.h CharBonus.h \
 WordBonus.h
	    g++ -Wall -c Field.cpp -o Field.o `pkg-config --cflags --libs gtk+-2.0`
Game.o: Game.cpp Game.h Map.h Character.h Field.h Gtk.h CharBonus.h \
 WordBonus.h Player.h Sack.h Dictionary.h Human.h HumanBox.h HumanChar.h \
 Computer.h History.h
	    g++ -Wall -c Game.cpp -o Game.o `pkg-config --cflags --libs gtk+-2.0`
Gtk.o: Gtk.cpp Game.h Map.h Character.h Field.h Gtk.h CharBonus.h \
 WordBonus.h Player.h Sack.h Dictionary.h Human.h HumanBox.h HumanChar.h \
 Computer.h History.h
	    g++ -Wall -c Gtk.cpp -o Gtk.o `pkg-config --cflags --libs gtk+-2.0`
History.o: History.cpp History.h Map.h Character.h Field.h Gtk.h \
 CharBonus.h WordBonus.h Player.h Sack.h Dictionary.h
	    g++ -Wall -c History.cpp -o History.o `pkg-config --cflags --libs gtk+-2.0`
HumanBox.o: HumanBox.cpp Human.h Player.h Sack.h Character.h Map.h \
 Field.h Gtk.h CharBonus.h WordBonus.h Dictionary.h HumanBox.h \
 HumanChar.h
	    g++ -Wall -c HumanBox.cpp -o HumanBox.o `pkg-config --cflags --libs gtk+-2.0`
HumanChar.o: HumanChar.cpp HumanBox.h HumanChar.h Character.h Gtk.h
	    g++ -Wall -c HumanChar.cpp -o HumanChar.o `pkg-config --cflags --libs gtk+-2.0`
Human.o: Human.cpp Human.h Player.h Sack.h Character.h Map.h Field.h \
 Gtk.h CharBonus.h WordBonus.h Dictionary.h HumanBox.h HumanChar.h
	    g++ -Wall -c Human.cpp -o Human.o `pkg-config --cflags --libs gtk+-2.0`
main.o: main.cpp Game.h Map.h Character.h Field.h Gtk.h CharBonus.h \
 WordBonus.h Player.h Sack.h Dictionary.h Human.h HumanBox.h HumanChar.h \
 Computer.h History.h
	    g++ -Wall -c main.cpp -o main.o `pkg-config --cflags --libs gtk+-2.0`
Map.o: Map.cpp Map.h Character.h Field.h Gtk.h CharBonus.h WordBonus.h
	    g++ -Wall -c Map.cpp -o Map.o `pkg-config --cflags --libs gtk+-2.0`
Player.o: Player.cpp Player.h Sack.h Character.h Map.h Field.h Gtk.h \
 CharBonus.h WordBonus.h Dictionary.h
	    g++ -Wall -c Player.cpp -o Player.o `pkg-config --cflags --libs gtk+-2.0`
Sack.o: Sack.cpp Sack.h Character.h
	    g++ -Wall -c Sack.cpp -o Sack.o `pkg-config --cflags --libs gtk+-2.0`
WordBonus.o: WordBonus.cpp WordBonus.h Field.h Character.h Gtk.h
	    g++ -Wall -c WordBonus.cpp -o WordBonus.o `pkg-config --cflags --libs gtk+-2.0`
clean:
	      rm *.o
	      rm main
