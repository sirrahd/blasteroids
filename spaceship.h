#include <allegro5/allegro.h>

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

Spaceship* create_ship();
void rotate_ship(Spaceship* s);
void accelerate_ship(Spaceship* s, int direction);
void destroy_ship(Spaceship* s);
void draw_ship(Spaceship *s);
