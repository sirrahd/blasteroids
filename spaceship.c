#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"

void spaceship_draw(Object* o) {
	al_draw_line(-8, 9, 0, -11, o->structure.color, 3.0f);
	al_draw_line(0, -11, 8, 9, o->structure.color, 3.0f);
	al_draw_line(-6, 4, -1, 4, o->structure.color, 3.0f);
	al_draw_line(6, 4, 1, 4, o->structure.color, 3.0f);
	if (o->acceleration.x || o->acceleration.y) {
		al_draw_line(-8, 9, 8, 9, al_map_rgb(255,0,0), 3.0f);
	}
}

void spaceship_define(Object* o, Euclidean resolution) {
	o->type = Spaceship;

	o->speed_limit = 3.0;

	o->position.x = resolution.x / 2.0 + o->structure.size / 2.0;
	o->position.y = resolution.y / 2.0 + o->structure.size / 2.0;
	o->position.r = 0.0;

  o->velocity.x = 0.0;
  o->velocity.y = 0.0;
  o->velocity.r = 0.0;
  
	o->acceleration.x = 0.0;
	o->acceleration.y = 0.0;
	o->acceleration.r = 0.0;

	o->structure.size = 15.0;
	o->structure.color = al_map_rgb(0,255,0);
	
	o->state.no_blast = 0;
	o->state.no_accel = 0;
	o->state.dead = 0;
}

