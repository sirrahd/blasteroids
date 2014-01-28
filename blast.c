#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

void draw_blast(Object* o) {
	al_draw_filled_rectangle(-2, -2, 2, 2, o->structure.color);
}

Object* new_blast(Object* owner) {
	if(owner->state.value == 2)
		return;
	owner->state.value = Charging;
	owner->state.time = 5;
	Object* o = new_object();
	o->type = Blast;
	o->state.value = Dead;
	o->state.time = 40;
	o->max_speed = 10.0;
	o->structure.size = 5.0;
	o->structure.color = al_map_rgb(255,255,255);
	o->state.time = 50;
	o->position.x = owner->position.x;
	o->position.y = owner->position.y;
	o->position.r = owner->position.r;
	o->velocity.x = o->max_speed * sinf(o->position.r);
	o->velocity.y = o->max_speed * cosf(o->position.r);
}
