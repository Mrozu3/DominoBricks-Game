#ELEMENTY KOMPILACJI
CC = g++
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#PLIKI
FILENAME = `basename $(CURDIR)`
TAR = $(FILENAME).tar.gz

#INSTRUKCJE
all:
	@echo "** Tworzenie klockow"
	$(CC) -c "Main.cpp" -o Main.o
	$(CC) -c "Game.cpp" -o Game.o
	$(CC) -c "Enemy.cpp" -o Enemy.o
	@echo "** Ukladanie domino..."
	$(CC) -o DominoBricks Main.o Game.o Enemy.o $(LIBS)
	@echo "** Gra gotowa do uruchomienia..."


#Przykadowe uruchomienia
.PHONY: Domino
Domino: DominoBricks
	 ./DominoBricks

#CZYSZCZENIE ZE ZBEDNYCH PLIKOW I PAKOWANIE
.PHONY: clear cleardomino tar cleartar
cleardomino:
	rm -f DominoBricks
clear:                                                     
	rm -f *.o *~ *.a *.x *.gch *.out *.tar.gz 

tar: clear
	(cd ../; tar cvzf $(TAR) $(FILENAME) )

cleartar:
	(cd ../; rm -f $(FILENAME).tar.gz )
