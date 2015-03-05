#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "blast.h"

void blast_draw(Object* o) {
	al_draw_filled_rectangle(-2, -2, 2, 2, o->structure.color);
}

void blast_define(Object* o, Euclidean start) {
	o->type = Blast;

	o->speed_limit = 10.0;

	o->position.x = start.x;
	o->position.y = start.y;
	o->position.r = start.r;

	o->velocity.x = o->speed_limit * sinf(o->position.r);
	o->velocity.y = o->speed_limit * cosf(o->position.r);
  o->velocity.r = 0.0;
  
	o->acceleration.x = 0.0;
	o->acceleration.y = 0.0;
	o->acceleration.r = 0.0;

	o->structure.size = 5.0;
	o->structure.color = al_map_rgb(255,255,255);
	
	o->state.no_accel = 0;
	o->state.no_blast = 0;
	o->state.dead = 40;
}
