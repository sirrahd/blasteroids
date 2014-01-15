CC=gcc
W=-Werror
CFLAGS=-O3 -lallegro -lallegro_primitives -lm -p
DEBUGFLAGS=$(CFLAGS) $(W) -g
OBJECTS=blasteroids.o object.o

blasteroids: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
	./blasteroids > latest.out

blasteroids.o: blasteroids.c blasteroids.h
	$(CC) $(CFLAGS) $(W) -c $^

object.o: object.c blasteroids.h
	$(CC) $(CFLAGS) $(W) -c $^
	
debug: *.c
	$(CC) $(DEBUGFLAGS) $^ -o blasteroids
	valgrind --leak-check=full --track-origins=yes ./blasteroids

clean:
	rm *.o
	rm *.gch
	rm blasteroids
	rm core
	rm *.out
