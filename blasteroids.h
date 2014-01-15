#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

extern const float FPS;
extern const float SCREEN_X;
extern const float SCREEN_Y;

typedef enum {
	Spaceship,
	Asteroid,
	Blast
} Type;

typedef struct Object {
	int id;
	Type type;
	struct {
		float x;
		float y;
	} position;
	struct {
		float x;
		float y;
		float r;
	} speed;
	float heading;
	float acceleration;
	float size;
	int max_speed;
	int state;
	ALLEGRO_COLOR color;
	struct Object* next;
} Object;

void abort_game(const char* message);

void clean();
void draw_all();
Object* create();
