#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "common.h"
#include "spaceship.h"

void draw_ship(Spaceship*);

const int SHIP_DIM_X = 20;
const int SHIP_DIM_Y = 20;
const float SHIP_MAX_SPEED = 5.0;
const float SHIP_ACCELERATION = 0.2;

Spaceship* create_ship() {
	Spaceship* s = malloc(sizeof(Spaceship));
	s->x = SCREEN_X / 2;
	s->y = SCREEN_Y / 2;
	s->heading = 0;
	s->gone = false;
	s->accel = false;
	s->bitmap = al_create_bitmap(SHIP_DIM_X, SHIP_DIM_Y);
	if(!s->bitmap)
		error("Couldn't create spaceship");
	draw_ship(s);
	return s;
}

void move_ship(Spaceship* s, int direction) {
	rotate_ship(s);
	s->speed_x -= SHIP_ACCELERATION * sinf(s->heading) * direction;
	s->speed_y += SHIP_ACCELERATION * cosf(s->heading) * direction;
	if (fabs(s->speed_x) > SHIP_MAX_SPEED)
		s->speed_x = SHIP_MAX_SPEED * s->speed_x / fabs(s->speed_x);
	if (fabs(s->speed_y) > SHIP_MAX_SPEED)
		s->speed_y = SHIP_MAX_SPEED * s->speed_y / fabs(s->speed_y);

	s->x += s->speed_x;
	s->y += s->speed_y;
	
	if (s->x > SCREEN_X - SHIP_DIM_X / 2)
		s->x -= SCREEN_X;
	else if (s->x < -SHIP_DIM_X / 2)
		s->x += SCREEN_X;
	
	if (s->y > SCREEN_Y - SHIP_DIM_Y / 2)
		s->y -= SCREEN_Y;
	else if (s->y < - SHIP_DIM_Y / 2)
		s->y += SCREEN_Y;
}

void rotate_ship(Spaceship* s) {
	s->heading = rotate(s->heading, s->rotate);
//	al_set_target_bitmap(s->bitmap);
//	ALLEGRO_TRANSFORM transform;
//	al_rotate_transform(&transform, s->heading);
//	al_use_transform(&transform);
}

void destroy_ship(Spaceship* s) {
	al_destroy_bitmap(s->bitmap);
	free(s);
}

void draw_ship(Spaceship* s)
{
	move_ship(s, s->accel);
	al_set_target_bitmap(s->bitmap);
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, s->heading);
	al_translate_transform(&transform, SHIP_DIM_X / 2, SHIP_DIM_Y / 2);
	al_use_transform(&transform);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_line(-8, 9, 0, -11, al_map_rgb(0,255,0), 3.0f);
	al_draw_line(0, -11, 8, 9, al_map_rgb(0,255,0), 3.0f);
	al_draw_line(-6, 4, -1, 4, al_map_rgb(0,255,0), 3.0f);
	al_draw_line(6, 4, 1, 4, al_map_rgb(0,255,0), 3.0f);
	
	if (s->accel == 1) {
		al_draw_line(-8, 9, 8, 9, al_map_rgb(255,0,0), 3.0f);
	}
	else if (s->accel == -1) {
		al_draw_line(-8, 9, 8, 9, al_map_rgb(0,0,255), 3.0f);
	}
	
	al_identity_transform(&transform);
	al_use_transform(&transform);
}

