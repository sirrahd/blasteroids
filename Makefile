CC=gcc
W=-Werror
CFLAGS=-lallegro -lallegro_primitives -lm -p
COPTS=-O3
DEBUGFLAGS=$(CFLAGS) $(W) -g

SOURCES=blasteroids.c game.c object.c asteroid.c list.c spaceship.c blast.c
OBJECTS=$(addprefix $(OUTDIR)/,$(SOURCES:.c=.o))

default: clean debug run

production: $(SOURCES)
	$(CC) $^ -o blasteroids $(COPTS) $(CFLAGS) 
	./blasteroids
	
debug: $(SOURCES)
	$(CC) $^ -o blasteroids $(DEBUGFLAGS)

run:
	valgrind --leak-check=full --track-origins=yes ./blasteroids > valgrind.out 2>&1

clean:
	rm -f *.o
	rm -f *.gch
	rm -f blasteroids
	rm -f core
	rm -f *.out
	rm -f vgcore.*
