#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

void draw_asteroid(Object* o) {
	al_draw_line(-20, 20, -25, 5, o->structure.color, 2.0f);
	al_draw_line(-25, 5, -25, -10, o->structure.color, 2.0f);
	al_draw_line(-25, -10, -5, -10, o->structure.color, 2.0f);
	al_draw_line(-5, -10, -10, -20, o->structure.color, 2.0f);
	al_draw_line(-10, -20, 5, -20, o->structure.color, 2.0f);
	al_draw_line(5, -20, 20, -10, o->structure.color, 2.0f);
	al_draw_line(20, -10, 20, -5, o->structure.color, 2.0f);
	al_draw_line(20, -5, 0, 0, o->structure.color, 2.0f);
	al_draw_line(0, 0, 20, 10, o->structure.color, 2.0f);
	al_draw_line(20, 10, 10, 20, o->structure.color, 2.0f);
	al_draw_line(10, 20, 0, 15, o->structure.color, 2.0f);
	al_draw_line(0, 15, -20, 20, o->structure.color, 2.0f);
}

Object* new_asteroid() {
	Object* o = new_object();
	o->type = Asteroid;
	o->structure.size = 40.0;
	o->structure.color = al_map_rgb(0,255,255);
	o->position.x = rand() % (int)game->resolution.x;
	o->position.y = rand() % (int)game->resolution.y;
	o->max_speed = 3.0;
	o->velocity.x = (float)rand() / (float)RAND_MAX * o->max_speed * 2.0 - o->max_speed;
	o->velocity.y = (float)rand() / (float)RAND_MAX * o->max_speed * 2.0 - o->max_speed;
	o->velocity.r = (float)rand() / (float)RAND_MAX - 0.5;
	o->acceleration.x = 0.0;
	o->acceleration.y = 0.0;
	o->acceleration.r = 0.0;
	
	return o;
}