jeux: jeux.o struc.o
	gcc jeux.o struc.o -o jeux -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2
jeux.o: jeux.c struc.h
	gcc -c jeux.c
struc.o: struc.c struc.h
	gcc -c struc.c
clean :
	rm -f *.o