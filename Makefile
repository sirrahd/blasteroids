CC=gcc
W=-Werror
CFLAGS=-O3 -lallegro -lallegro_primitives -lm -p
DEBUGFLAGS=$(CFLAGS) $(W) -g
OBJECTS=blasteroids.o object.o

blasteroids: $(OBJECTS)
	$(CC) $^ -o $@  $(CFLAGS)

blasteroids.o: blasteroids.c blasteroids.h
	$(CC) $(CFLAGS) $(W) -c $^

object.o: object.c blasteroids.h
	$(CC) $(CFLAGS) $(W) -c $^
	
debug: *.c
	$(CC) $(DEBUGFLAGS) $^ -o blasteroids
	valgrind --leak-check=full --track-origins=yes ./blasteroids

clean:
	rm -f *.o
	rm -f *.gch
	rm -f blasteroids
	rm -f core
	rm -f *.out
	rm -f vgcore.*
