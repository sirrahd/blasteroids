#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "object.h"
#include "spaceship.h"
#include "asteroid.h"
#include "blast.h"

// Creates a new object
Object* object_new(Type type, Euclidean resolution)
{
	Object* o = malloc(sizeof(Object));
	switch(type) {
    case Spaceship:
    	spaceship_define(o, resolution);
      break;
    case Asteroid:
      asteroid_define(o, resolution);
      break;
    case Blast:
      blast_define(o, resolution);
      break;
	 }
	return o;
}
	
// Deletes an object
void object_delete(Object* object) {
	//TODO
	return;
	//list_remove(game->objects, o);
	//free(o);
}

void prepare_transform(Object* o, Euclidean position)
{
	ALLEGRO_TRANSFORM transform;
#ifdef DEBUG
	al_identity_transform(&transform);
	al_translate_transform(&transform, position.x, position.y);
	al_use_transform(&transform);
	al_draw_filled_rectangle(-o->structure.size / 2.0, -o->structure.size / 2.0, o->structure.size / 2.0, o->structure.size / 2.0, al_map_rgb(255,255,255));
#endif

  al_identity_transform(&transform);
	al_rotate_transform(&transform, o->position.r);
	al_translate_transform(&transform, position.x, position.y);
	al_use_transform(&transform);
}

void call_draw(Object* o) {
	switch(o->type) {
		case Spaceship:
			spaceship_draw(o);
			break;
		case Asteroid:
			asteroid_draw(o);
			break;
		case Blast:
			blast_draw(o);
			break;
	}
}

void object_draw(Object* o, Euclidean resolution) {
  prepare_transform(o, o->position);
  call_draw(o);
  if (o->mirror.x != o->position.x || o->mirror.y != o->position.y) {
    prepare_transform(o, o->mirror);
    call_draw(o);
  }
}

void update_state(Object* o) {
  if (o->state.no_blast > 0)
    --o->state.no_blast;
  if (o->state.no_accel > 0)
    --o->state.no_accel;
  if (o->state.dead > 0)
    --o->state.dead;
}

void update_velocity(Object* o) {
  o->velocity.x += o->acceleration.x;	
	o->velocity.y += o->acceleration.y;
	
	if (fabs(o->velocity.x) > o->speed_limit)
	  o->velocity.x = o->speed_limit * o->velocity.x / fabs(o->velocity.x);
	  
	if (fabs(o->velocity.y) > o->speed_limit)
	  o->velocity.y = o->speed_limit * o->velocity.y / fabs(o->velocity.y);
}

float rotate(float heading, float speed) {
  const float rotation_unit = (float)(M_PI / 32.0);
  while(fabs(heading) > 2 * M_PI) {
    if(heading > 0)
      heading -= 2 * M_PI;
    else
      heading += 2 * M_PI;
  }
  return heading + rotation_unit * speed;
}

void update_position(Object* o, Euclidean boundaries) {
	o->position.r = rotate(o->position.r, o->velocity.r);
	o->position.x += o->velocity.x;
	o->position.y -= o->velocity.y;
	if (o->position.x > boundaries.x)
		o->position.x -= boundaries.x;
	else if (o->position.x < 0)
		o->position.x += boundaries.x;
	if (o->position.y > boundaries.y)
		o->position.y -= boundaries.y;
	else if (o->position.y < 0)
		o->position.y += boundaries.y;

	if (o->position.x + o->structure.size / 2 > boundaries.x)
		o->mirror.x = o->position.x - boundaries.x;
	else if (o->position.x - o->structure.size / 2 < 0)
		o->mirror.x = o->position.x + boundaries.x;
	else
	  o->mirror.x = o->position.x;
	if (o->position.y + o->structure.size / 2 > boundaries.y)
		o->mirror.y = o->position.y - boundaries.y;
	else if (o->position.y - o->structure.size / 2 < 0)
		o->mirror.y = o->position.y + boundaries.y;
	else
	  o->mirror.y = o->position.y;
}

void object_move(Object* o, List* list, Euclidean boundaries) {
  update_state(o);
  update_velocity(o);
  update_position(o, boundaries);
  //check collisions
}
/*
// Modifies objects o and p in response to a collision
void collide_object(Object* o, Object* p) {
	if(
		(o->type == Blast && p == game->ship)
		|| (p->type == Blast && o == game->ship)
		|| (o->type == Blast && p->type == Blast)
	)
		return;
	
	o->state.value = o->state.value | (Collision | EngineFail);
	p->state.value = p->state.value | (Collision | EngineFail);
	o->state.time = p->state.time = 10;
	
	Euclidean vo;
	Euclidean vp;
	
	vo.x = (o->velocity.x * (o->structure.size - p->structure.size) + 2 * p->structure.size * p->velocity.x)
		/ (o->structure.size + p->structure.size);
	vo.y = (o->velocity.y * (o->structure.size - p->structure.size) + 2 * p->structure.size * p->velocity.y)
		/ (o->structure.size + p->structure.size);
	vo.r = (o->velocity.r * (o->structure.size - p->structure.size) + 2 * p->structure.size * p->velocity.r)
		/ (o->structure.size + p->structure.size);
	vp.x = (p->velocity.x * (p->structure.size - o->structure.size) + 2 * o->structure.size * o->velocity.x)
		/ (p->structure.size + o->structure.size);
	vp.y = (p->velocity.y * (p->structure.size - o->structure.size) + 2 * o->structure.size * o->velocity.y)
		/ (p->structure.size + o->structure.size);
	vp.r = (p->velocity.r * (p->structure.size - o->structure.size) + 2 * o->structure.size * o->velocity.r)
		/ (p->structure.size + o->structure.size);
		
	o->velocity.x = vo.x;
	o->velocity.y = vo.y;
	o->velocity.r = vo.r;
	p->velocity.x = vp.x;
	p->velocity.y = vp.y;
	p->velocity.r = vp.r;
	
	if(o->type == Blast && p->type == Asteroid) {
		o->state.value = o->state.value | Dead;
		o->state.time = 0;
		p->state.value = p->state.value | Dead;
		p->state.time = 60;
	}
	else if(o->type == Asteroid && p->type == Blast) {
		o->state.value = o->state.value | Dead;
		o->state.time = 60;
		p->state.value = p->state.value | Dead;
		p->state.time = 0;
	}
	else if(o->type == Spaceship && p->type == Asteroid) {
		o->state.value = o->state.value | Dead;
		o->state.time = 60;
		p->state.value = p->state.value | Dead;
		p->state.time = 60;
	}
	else if(o->type == Asteroid && p->type == Spaceship) {
		o->state.value = o->state.value | Dead;
		o->state.time = 60;
		p->state.value = p->state.value | Dead;
		p->state.time = 60;
}

// Scans the game list for any collisions with the object after the object
// Based on the current state of the game list
int collision_scan(Object* o, int x, int y) {
	Object* p = NULL;
	List child = {
		.start = game->objects->current,
		.current = game->objects->current
	};
	for(p = list_next(&child); p != NULL; p = list_next(&child)) {
		if (
			((p->position.x - p->structure.size / 2.0 > x - o->structure.size / 2.0
			&& p->position.x - p->structure.size / 2.0 < x + o->structure.size / 2.0)
			||
			(p->position.x + p->structure.size / 2.0 > x - o->structure.size / 2.0
			&& p->position.x + p->structure.size / 2.0 < x + o->structure.size / 2.0)
			||
			(x - o->structure.size / 2.0 > p->position.x - p->structure.size / 2.0
			&& x - o->structure.size / 2.0 < p->position.x + p->structure.size / 2.0)
			||
			(x + o->structure.size / 2.0 > p->position.x - p->structure.size / 2.0
			&& x + o->structure.size / 2.0 < p->position.x + p->structure.size / 2.0))
			&&
			((p->position.y - p->structure.size / 2.0 > y - o->structure.size / 2.0
			&& p->position.y - p->structure.size / 2.0 < y + o->structure.size / 2.0)
			||
			(p->position.y + p->structure.size / 2.0 > y - o->structure.size / 2.0
			&& p->position.y + p->structure.size / 2.0 < y + o->structure.size / 2.0)
			||
			(y - o->structure.size / 2.0 > p->position.y - p->structure.size / 2.0
			&& y - o->structure.size / 2.0 < p->position.y + p->structure.size / 2.0)
			||
			(y + o->structure.size / 2.0 > p->position.y - p->structure.size / 2.0
			&& y + o->structure.size / 2.0 < p->position.y + p->structure.size / 2.0))
		) {
			collide_object(o, p);
			return 1;
		}
	}
	
	return 0;
}

void object_state_transition(Object* o) {
	
	if(o->state.value & Dead) {
		delete_object(o);
		return;
	}
	if(o->state.value & Charging) {
		o->state.value = o->state.value & !Charging;
	}
	if(o->state.value & Collision) {
		o->state.value = o->state.value & !Collision;
	}
}

void move_object(Object* o) {
	// Velocity
	if(o->state.value & EngineFail) {
		o->acceleration.x = o->acceleration.y = o->acceleration.r = 0;
	}
	
	o->velocity.x += o->acceleration.x;
	if(fabs(o->velocity.x) > o->max_speed)
		o->velocity.x = o->max_speed * o->velocity.x / fabs(o->velocity.x);
	
	o->velocity.y += o->acceleration.y;
	if(fabs(o->velocity.y) > o->max_speed)
		o->velocity.y = o->max_speed * o->velocity.y / fabs(o->velocity.y);
		
	// Position
	o->position.r = rotate(o->position.r, o->velocity.r);
	o->position.x += o->velocity.x;
	o->position.y -= o->velocity.y;
	if (o->position.x > game->resolution.x)
		o->position.x -= game->resolution.x;
	else if (o->position.x < -o->structure.size / 2.0)
		o->position.x += game->resolution.x;
	if (o->position.y > game->resolution.y)
		o->position.y -= game->resolution.y;
	else if (o->position.y < - o->structure.size / 2.0)
		o->position.y += game->resolution.y;
	
	// Check for collisions
	if(!(o->state.value & Collision)) {
		if(!collision_scan(o, o->position.x, o->position.y)) {
			if (o->position.x + o->structure.size / 2 > game->resolution.x)
				collision_scan(o, o->position.x - game->resolution.x, o->position.y);
			else if (o->position.x - o->structure.size / 2 < 0)
				collision_scan(o, o->position.x + game->resolution.x, o->position.y);
			if (o->position.y + o->structure.size / 2 > game->resolution.y)
				collision_scan(o, o->position.x, o->position.y - game->resolution.y);
			else if (o->position.y - o->structure.size / 2 < 0)
				collision_scan(o, o->position.x, o->position.y + game->resolution.y);
		}
	}
  return;
}*/
