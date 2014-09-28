#pragma once

#include <allegro5/allegro.h>
#include <math.h>
#include "list.h"
#include "object.h"

typedef struct {
	Euclidean resolution;
	int lives;
	List* objects;
	Object* ship;
	ALLEGRO_MUTEX* mutex;
} Game;

Game* game_new(int resX, int resY);
void game_draw(Game* game);
void game_move(Game* game);
void ship_rotate(Object* o, int direction);
void ship_accelerate(Object* o, float linear);
void game_delete();

