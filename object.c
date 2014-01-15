#include "blasteroids.h"

const float FPS = 60;
const float SCREEN_X = 640;
const float SCREEN_Y = 480;

Object* ship = NULL;

void destroy(Object* o) {
	Object* previous;

	if (ship->id == o->id) {
		ship = o->next;
		free(o);
		return;
	}
	
	for (previous = ship; previous->next->id != o->id; previous = previous->next);
	
	previous->next = o->next;
		
	free(o);
}

float rotate(float heading, float speed) {
	const float rotation_unit = (float)(M_PI / 16.0);
	
	return heading + rotation_unit * speed;
}


void collide(Object* o) {
Object* i;
	for (i = o->next; i != NULL; i = i->next) {
		if (
			((i->position.x - i->size / 2.0 > o->position.x - o->size / 2.0
			&& i->position.x - i->size / 2.0 < o->position.x + o->size / 2.0)
			||
			(i->position.x + i->size / 2.0 > o->position.x - o->size / 2.0
			&& i->position.x + i->size / 2.0 < o->position.x + o->size / 2.0)
			||
			(o->position.x - o->size / 2.0 > i->position.x - i->size / 2.0
			&& o->position.x - o->size / 2.0 < i->position.x + i->size / 2.0)
			||
			(o->position.x + o->size / 2.0 > i->position.x - i->size / 2.0
			&& o->position.x + o->size / 2.0 < i->position.x + i->size / 2.0))
			&&
			((i->position.y - i->size / 2.0 > o->position.y - o->size / 2.0
			&& i->position.y - i->size / 2.0 < o->position.y + o->size / 2.0)
			||
			(i->position.y + i->size / 2.0 > o->position.y - o->size / 2.0
			&& i->position.y + i->size / 2.0 < o->position.y + o->size / 2.0)
			||
			(o->position.y - o->size / 2.0 > i->position.y - i->size / 2.0
			&& o->position.y - o->size / 2.0 < i->position.y + i->size / 2.0)
			||
			(o->position.y + o->size / 2.0 > i->position.y - i->size / 2.0
			&& o->position.y + o->size / 2.0 < i->position.y + i->size / 2.0))
		) {
			// A collision occurred between i and o
			if (o->type == Spaceship && i->type == Blast ||
				o->type == Asteroid && i->type == Asteroid)
				continue;
			
			destroy(o);
			destroy(i);
			
		}
	}
}

void move(Object* o) {
	// Check for collisions
	collide(o);
	
	// Heading
	o->heading = rotate(o->heading, o->speed.r);
	
	// Velocity
	o->speed.x += o->acceleration * sinf(o->heading);
	o->speed.y += o->acceleration * cosf(o->heading);
	if (fabs(o->speed.x) > o->max_speed)
		o->speed.x = o->max_speed * o->speed.x / fabs(o->speed.x);
	if (fabs(o->speed.y) > o->max_speed)
		o->speed.y = o->max_speed * o->speed.y / fabs(o->speed.y);
		
	// Distance
	o->position.x += o->speed.x;
	o->position.y -= o->speed.y;
	if (o->position.x > SCREEN_X - o->size / 2.0)
		o->position.x -= SCREEN_X;
	else if (o->position.x < -o->size / 2.0)
		o->position.x += SCREEN_X;
	if (o->position.y > SCREEN_Y - o->size / 2.0)
		o->position.y -= SCREEN_Y;
	else if (o->position.y < - o->size / 2.0)
		o->position.y += SCREEN_Y;
		
	// State recovery
	if (o->state > 0) {
		o->state -= 1;
	}
	else if (o->state < -1) {
		o->state += 1;
	}
}

void draw(Object* o) {
	move(o);
	ALLEGRO_TRANSFORM transform;
	// for hit target tracking
	al_identity_transform(&transform);
	al_translate_transform(&transform, o->position.x + o->size / 2.0, o->position.y + o->size / 2.0);
	al_use_transform(&transform);
	//al_draw_filled_rectangle(-o->size / 2.0, -o->size / 2.0, o->size / 2.0, o->size / 2.0, al_map_rgb(255,255,255));
	al_identity_transform(&transform);
	al_rotate_transform(&transform, o->heading);
	al_translate_transform(&transform, o->position.x + o->size / 2.0, o->position.y + o->size / 2.0);
	al_use_transform(&transform);
	if (o->type == Asteroid) {
		al_draw_line(-20, 20, -25, 5, o->color, 2.0f);
		al_draw_line(-25, 5, -25, -10, o->color, 2.0f);
		al_draw_line(-25, -10, -5, -10, o->color, 2.0f);
		al_draw_line(-5, -10, -10, -20, o->color, 2.0f);
		al_draw_line(-10, -20, 5, -20, o->color, 2.0f);
		al_draw_line(5, -20, 20, -10, o->color, 2.0f);
		al_draw_line(20, -10, 20, -5, o->color, 2.0f);
		al_draw_line(20, -5, 0, 0, o->color, 2.0f);
		al_draw_line(0, 0, 20, 10, o->color, 2.0f);
		al_draw_line(20, 10, 10, 20, o->color, 2.0f);
		al_draw_line(10, 20, 0, 15, o->color, 2.0f);
		al_draw_line(0, 15, -20, 20, o->color, 2.0f);
	}
	else if (o->type == Spaceship) {
		al_draw_line(-8, 9, 0, -11, o->color, 3.0f);
		al_draw_line(0, -11, 8, 9, o->color, 3.0f);
		al_draw_line(-6, 4, -1, 4, o->color, 3.0f);
		al_draw_line(6, 4, 1, 4, o->color, 3.0f);
		if (o->acceleration > 0) {
			al_draw_line(-8, 9, 8, 9, al_map_rgb(255,0,0), 3.0f);
		}
		else if (o->acceleration < 0) {
			al_draw_line(-8, 9, 8, 9, al_map_rgb(0,0,255), 3.0f);
		}
	}
	else if (o->type == Blast) {
		al_draw_filled_rectangle(-2, -2, 2, 2, o->color);
	}
	
	al_identity_transform(&transform);
	al_use_transform(&transform);
}

Object* create(Type type) {
	static int id = 0;
	
	// Don't need to explicitly create the user's ship.
	if (!ship && type != Spaceship)
		abort_game("Need to create Spaceship first");
	
	// Only make blast if the ship has energy
	if (ship->state > 0 && type == Blast)
		return NULL;
		
	Object* o = (Object*)malloc(sizeof(Object));
	o->id = id++;
	o->type = type;
	o->position.x = 0;
	o->position.y = 0;
	o->speed.x = 0;
	o->speed.y = 0;
	o->speed.r = 0;
	o->heading = 0;
	o->acceleration = 0;
	o->size = 0;
	o->max_speed = 5;
	o->state = 0;
	o->color = al_map_rgb(255,255,255);
	o->next = NULL;
	if (type == Spaceship) {
		o->size = 15.0;
		o->position.x = SCREEN_X / 2.0 + o->size / 2.0;
		o->position.y = SCREEN_Y / 2.0 + o->size / 2.0;
		o->color = al_map_rgb(0,255,0);
	}
	else if (type == Asteroid) {
		o->size = 40.0;
		o->position.x = rand() % (int)SCREEN_X;
		o->position.y = rand() % (int)SCREEN_Y;
		o->heading = (float)rand();
		o->speed.x = (float)rand() / (float)RAND_MAX * o->max_speed * 2.0 - o->max_speed;
		o->speed.y = (float)rand() / (float)RAND_MAX * o->max_speed * 2.0 - o->max_speed;
		o->speed.r = 0.2;//(float)rand() / (float)RAND_MAX * 2.0 - 1.0;
		o->color = al_map_rgb(0,255,255);
	}
	else if (type == Blast) {
		ship->state = 5;
		o->max_speed = 10.0;
		o->state = -40;
		o->size = 5.0;
		o->heading = ship->heading;
		o->position.x = ship->position.x + 8;
		o->position.y = ship->position.y + fabs(8 * sinf(o->heading));
		o->speed.x = o->max_speed * sinf(o->heading);
		o->speed.y = o->max_speed * cosf(o->heading);
		o->color = al_map_rgb(255,255,255);
	}
	
	if (!ship) {
		ship = o;
	}
	else if (!ship->next) {
		ship->next = o;
	}
	else {
		o->next = ship->next;
		ship->next = o;
	}
	
	return o;
}

void clean() {
	Object* o;
	for (o = ship; o != NULL; o = o->next)
		if (o->state == -1)
			destroy(o);
}

void draw_all() {
	Object* o;
	for (o = ship; o != NULL; o = o->next) {
		draw(o);
	}
}

