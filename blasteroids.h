#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

typedef struct {
	enum {
		SPACESHIP,
		ASTEROID
	} type;
	struct {
		float x;
		float y;
	} location;
	struct {
		float x;
		float y;
		float r;
	} speed;
	float heading;
	float acceleration;
	int gone;
	ALLEGRO_COLOR color;
	ALLEGRO_BITMAP* bitmap;
} Object;

typedef struct {
	float x;
	float y;
	float heading;
	float speed_x;
	float speed_y;
	int accel;
	float rotate;
	int gone;
	ALLEGRO_BITMAP* bitmap;
} Spaceship;

typedef struct {
	float x;
	float y;
	float heading;
	float speed_x;
	float speed_y;
	float rotate;
	float size;
	int gone;
	ALLEGRO_COLOR color;
	ALLEGRO_BITMAP* bitmap;
} Asteroid;

extern const float FPS;
extern const int SCREEN_X;
extern const int SCREEN_Y;

float rotate(float r, float direction);
/* returns: rotated coordinates in radians
 * float r: current direction
 * int direction: direction to rotate (1 for cw or -1 for ccw), or different
 * factor to change rotation speeds.
 */

Spaceship* create_ship();
void draw_ship(Spaceship *s);
void destroy_ship(Spaceship* s);

Asteroid* create_asteroid();
void draw_asteroid(Asteroid* a);
void destroy_asteroid(Asteroid* a);

//Maybe remove later
void rotate_ship(Spaceship* s);
