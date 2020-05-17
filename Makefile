#KOMPILACJA
.PHONY: all
all: 
	g++ -c main.cpp
	g++ -o main.out main.o -lsfml-graphics -lsfml-window -lsfml-system

	g++ -c Game.cpp
	g++ -o Game.out Game.o -lsfml-graphics -lsfml-window -lsfml-system

PHONY: clear tar cleartar
clear:                                                     
	rm -f *.o *~ *.a *.x *.gch *.out *.tar.gz 