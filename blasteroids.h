#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

//Maybe remove later
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	float x;
	float y;
	float heading;
	float speed_x;
	float speed_y;
	int accel;
	int rotate;
	int gone;
	ALLEGRO_BITMAP* bitmap;
} Spaceship;

extern const float FPS;
extern const int SCREEN_X;
extern const int SCREEN_Y;

float rotate(float r, int direction);
/* returns: rotated coordinates in radians
 * float r: current direction
 * int direction: direction to rotate (1 for cw or -1 for ccw)
 */

void accelerate_ship(Spaceship* s, int direction);
void destroy_ship(Spaceship* s);
void draw_ship(Spaceship *s);
Spaceship* create_ship();

//Maybe remove later

void warning(char* msg);
void error(char* msg);
void rotate_ship(Spaceship* s);
