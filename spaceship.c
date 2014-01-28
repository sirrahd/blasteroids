#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

void draw_spaceship(Object* o) {
	al_draw_line(-8, 9, 0, -11, o->structure.color, 3.0f);
	al_draw_line(0, -11, 8, 9, o->structure.color, 3.0f);
	al_draw_line(-6, 4, -1, 4, o->structure.color, 3.0f);
	al_draw_line(6, 4, 1, 4, o->structure.color, 3.0f);
	if (o->acceleration.x || o->acceleration.y) {
		al_draw_line(-8, 9, 8, 9, al_map_rgb(255,0,0), 3.0f);
	}
}

Object* new_spaceship() {
	Object* s = new_object();
	s->type = Spaceship;
	s->structure.size = 15.0;
	s->structure.color = al_map_rgb(0,255,0);
	s->position.x = game->resolution.x / 2.0 + s->structure.size / 2.0;
	s->position.y = game->resolution.y / 2.0 + s->structure.size / 2.0;
	s->max_speed = 5.0;
	
	return s;
}

