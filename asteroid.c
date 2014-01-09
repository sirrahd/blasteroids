#include "blasteroids.h"

int ASTEROID_DIM_X = 55;
int ASTEROID_DIM_Y = 55;

void rotate_asteroid(Asteroid* a) {
	a->heading = rotate(a->heading, a->rotate);
}

void move_asteroid(Asteroid* a) {
	rotate_asteroid(a);

	a->x += a->speed_x;
	a->y += a->speed_y;
	
	if (a->x > SCREEN_X - ASTEROID_DIM_X / 2)
		a->x -= SCREEN_X;
	else if (a->x < -ASTEROID_DIM_X / 2)
		a->x += SCREEN_X;
	
	if (a->y > SCREEN_Y - ASTEROID_DIM_Y / 2)
		a->y -= SCREEN_Y;
	else if (a->y < - ASTEROID_DIM_Y / 2)
		a->y += SCREEN_Y;
}

void draw_asteroid(Asteroid* a)
{
	move_asteroid(a);
	al_set_target_bitmap(a->bitmap);
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, a->heading);
	al_translate_transform(&transform, ASTEROID_DIM_X / 2, ASTEROID_DIM_Y / 2);
	al_use_transform(&transform);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_line(-20, 20, -25, 5, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(-25, 5, -25, -10, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(-25, -10, -5, -10, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(-5, -10, -10, -20, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(-10, -20, 5, -20, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(5, -20, 20, -10, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(20, -10, 20, -5, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(20, -5, 0, 0, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(0, 0, 20, 10, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(20, 10, 10, 20, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(10, 20, 0, 15, al_map_rgb(0,255,255), 2.0f);
	al_draw_line(0, 15, -20, 20, al_map_rgb(0,255,255), 2.0f);
		
	al_identity_transform(&transform);
	al_use_transform(&transform);
}

Asteroid* create_asteroid() {
	Asteroid* a = malloc(sizeof(Asteroid));
	a->x = rand() % SCREEN_X;
	a->y = rand() % SCREEN_Y;
	a->heading = (float)rand() / (float)RAND_MAX;
	a->speed_x = (float)rand() / (float)RAND_MAX * 3;
	a->speed_y = (float)rand() / (float)RAND_MAX * 3;
	a->rotate = (float)rand() / (float)RAND_MAX;
	a->gone = false;
	a->bitmap = al_create_bitmap(ASTEROID_DIM_X, ASTEROID_DIM_Y);
	if(!a->bitmap)
		error("Couldn't create asteroid");
		
	draw_asteroid(a);
	return a;
}

void destroy_asteroid(Asteroid* a) {
	al_destroy_bitmap(a->bitmap);
	free(a);
}

