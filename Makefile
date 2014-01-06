CC=gcc
W=-Werror
CFLAGS=-O3 -lallegro -lallegro_primitives -lm -p
DEBUGFLAGS=$(CFLAGS) $(W) -g
OBJECTS=blasteroids.o common.o spaceship.o

blasteroids: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ 
	./blasteroids

blasteroids.o: blasteroids.c blasteroids.h
	$(CC) $(CFLAGS) $(W) -c $^

common.o: common.c blasteroids.h
	$(CC) $(CFLAGS) $(W) -c $^

spaceship.o: spaceship.c blasteroids.h
	$(CC) $(CFLAGS) $(W) -c $^

debug: %.c
	$(CC) $(DEBUGFLAGS) $^ -o blasteroids

clean:
	rm -f *.o
	rm -f *.gch
	rm blasteroids
