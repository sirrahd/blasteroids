CC=gcc
W=-Werror
CFLAGS=-lallegro -lallegro_primitives -lm -p
COPTS=-O3
DEBUGFLAGS=$(CFLAGS) $(W) -g
OBJECTS=blasteroids.o object.o

default: clean debug run

production: *.c *.h
	$(CC) $^ -o blasteroids $(COPTS) $(CFLAGS) 
	
debug: *.c *.h
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
