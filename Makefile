blasteroids: blasteroids.o common.o spaceship.o
	gcc $^ -O3 -o blasteroids -lm -lallegro -lallegro_primitives
	./blasteroids

blasteroids.o: blasteroids.c common.h spaceship.h
	gcc -c -O3 $^

common.o: common.c
	gcc -c -O3 $^

spaceship.o: spaceship.c common.h spaceship.h
	gcc -c -O3 $^

debug: blasteroids.c
	gcc $^ -g -o blasteroids -lallegro
	
test: common_test.c common.c
	gcc $^ -o test

clean:
	rm -f *.o
	rm -f *.gch
	rm blasteroids
