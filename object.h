#include <allegro5/allegro.h>

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

Object* new_object();
void delete_object(Object* o);
void object_collide(Object* o, Object* p);
void rotate_object(Object* o, int direction);
void accelerate_object(Object* o, float linear);
void move_object(Object* o);
