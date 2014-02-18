#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"

// Creates a new object
Object* new_object()
{
	Object* o = malloc(sizeof(Object));
	list_add(game->objects, o);
	
	o->type = Spaceship;
	o->structure.size = 0.0;
	o->structure.color = al_map_rgb(0,0,0);
	o->state.value = 0;
	o->state.time = 0;
	o->position.x = 0;
	o->position.y = 0;
	o->position.r = 0.0;
	o->velocity.x = 0.0;
	o->velocity.y = 0.0;
	o->velocity.r = 0.0;
	o->acceleration.x = 0.0;
	o->acceleration.y = 0.0;
	o->acceleration.r = 0.0;
	o->max_speed = 0.0;
	
	return o;
}
	
// Deletes an object
void delete_object(Object* o) {
	list_remove(game->objects, o);
	free(o);
}

void draw_object(Object* o, float x, float y) {
	ALLEGRO_TRANSFORM transform;
	/* start for hit target tracking
	al_identity_transform(&transform);
	al_translate_transform(&transform, o->position.x, o->position.y);
	al_use_transform(&transform);
	al_draw_filled_rectangle(-o->structure.size / 2.0, -o->structure.size / 2.0, o->structure.size / 2.0, o->structure.size / 2.0, al_map_rgb(255,255,255));
	*/// end hit target tracking
	al_identity_transform(&transform);
	al_rotate_transform(&transform, o->position.r);
	al_translate_transform(&transform, x, y);
	al_use_transform(&transform);
	switch(o->type) {
		case Spaceship:
			draw_spaceship(o);
			break;
		case Asteroid:
			draw_asteroid(o);
			break;
		case Blast:
			draw_blast(o);
			break;
	}
	al_identity_transform(&transform);
	al_use_transform(&transform);
}

float rotate(float heading, float speed) {
	const float rotation_unit = (float)(M_PI / 16.0);
	while(fabs(heading) > 2 * M_PI) {
		if(heading > 0)
			heading -= 2 * M_PI;
		else
			heading += 2 * M_PI;
	}
	return heading + rotation_unit * speed;
}

void rotate_object(Object* o, int direction) {
	o->velocity.r = (float)direction;
}

void accelerate_object(Object* o, float linear) {
	o->acceleration.x = linear * sinf(o->position.r);
	o->acceleration.y = linear * cosf(o->position.r);
}

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
		o->state.value = 0->state.value | Dead;
		o->state.time = 60
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
}
