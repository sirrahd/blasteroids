#include <allegro5/allegro.h>
#include "list.h"

enum State {
	Normal = 0,
	Dead = 1,
	Charging = 1 << 1,
	Collision = 1 << 2,
	EngineFail = 1 << 3
};

typedef enum {
	Spaceship,
	Asteroid,
	Blast
} Type;

typedef struct {
	float x;
	float y;
	float r;
} Euclidean;

typedef struct {
	Type type;
	struct {
		float size;
		ALLEGRO_COLOR color;
	} structure;
	struct {
		int value;
		int time;
	} state;
	Euclidean position;
	Euclidean velocity;
	Euclidean acceleration;
	float max_speed;
} Object;

typedef struct {
	struct {
		int x;
		int y;
	} resolution;
	int lives;
	List* objects;
	Object* ship;
} Game;

Object* new_object();
void delete_object(Object* o);
void collide_object(Object* o, Object* p);
void rotate_object(Object* o, int direction);
void accelerate_object(Object* o, float linear);
void move_object(Object* o);
void draw_object(Object* o, float x, float y);
void object_state_transition(Object* o);

Object* new_spaceship();
void draw_spaceship(Object* o);

Object* new_blast(Object* owner);
void draw_asteroid(Object* o);

Object* new_asteroid();
void draw_asteroid(Object* o);

Game* new_game();
void delete_game();
void draw_screen();

extern Game* game;
