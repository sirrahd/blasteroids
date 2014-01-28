#include "list.h"
#include "object.h"
#include <stdio.h>

typedef struct {
	struct {
		int x;
		int y;
	} resolution;
	int lives;
	List* objects;
	Object* ship;
} Game;

extern Game* game;

Game* new_game();
void delete_game();
void draw_screen();

Object* new_spaceship();
Object* new_asteroid();
Object* new_blast(Object* owner);
void draw_spaceship(Object* o);
void draw_blast(Object* o);
void draw_asteroid(Object* o);
